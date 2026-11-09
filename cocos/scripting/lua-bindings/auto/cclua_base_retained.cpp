#include "scripting/lua-bindings/auto/cclua_base_auto.hpp"
#include "lua_conversion/lua_conversion.hpp"
#include "cocos2d.h"
#include "2d/CCProtectedNode.h"
#include "base/CCAsyncTaskPool.h"
#include "scripting/lua-bindings/manual/CCComponentLua.h"
#include "renderer/CCRenderer.h"
#include "renderer/CCPipelineDescriptor.h"
#include "renderer/backend/RenderTarget.h"
#include "scripting/lua-bindings/manual/tolua_fix.h"
#include "scripting/lua-bindings/manual/LuaBasicConversions.h"

// Remaining unsupported layouts/buffers and feature/platform bridges are enumerated in the convergence inventory.

// Retained: existing unsupported layout/value stub.
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

// Retained: existing unsupported layout/value stub.
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

// Retained: existing unsupported layout/value stub.
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

// Retained: feature condition.
#if CC_USE_PHYSICS
int lua_cc_base_Node_setPhysicsBody(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:setPhysicsBody");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Node::*)(cocos2d::PhysicsBody*)>(&cocos2d::Node::setPhysicsBody));
	LUA_INVOKE_FOOTER("1");
}
#endif

// Retained: feature condition.
#if CC_USE_PHYSICS
int lua_cc_base_Node_getPhysicsBody(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getPhysicsBody");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::PhysicsBody*(cocos2d::Node::*)()const>(&cocos2d::Node::getPhysicsBody));
	LUA_INVOKE_FOOTER("0");
}
#endif

// Retained: raw buffer/output or storage pointer.
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

// Retained: feature condition.
#if CC_USE_PHYSICS
int lua_cc_base_Scene_getPhysicsWorld(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Scene", "cc.Scene:getPhysicsWorld");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::PhysicsWorld*(cocos2d::Scene::*)()const>(&cocos2d::Scene::getPhysicsWorld));
	LUA_INVOKE_FOOTER("0");
}
#endif

// Retained: existing unsupported layout/value stub.
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

// Retained: existing unsupported layout/value stub.
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

// Retained: existing unsupported layout/value stub.
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

// Retained: existing unsupported layout/value stub.
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

// Retained: existing unsupported layout/value stub.
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

// Retained: existing unsupported layout/value stub.
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

// Retained: existing unsupported layout/value stub.
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

// Retained: existing unsupported layout/value stub.
int lua_cc_base_ParticleEmissionMaskCache_getEmissionMask(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ParticleEmissionMaskCache* cobj = nullptr;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ParticleEmissionMaskCache",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::ParticleEmissionMaskCache*)tolua_tousertype(tolua_S,1,0);
#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_ParticleEmissionMaskCache_getEmissionMask'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 1) {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.ParticleEmissionMaskCache:getEmissionMask");

            if (!ok) { break; }
            const cocos2d::ParticleEmissionMaskDescriptor& ret = cobj->getEmissionMask(arg0);
            #pragma warning NO CONVERSION FROM NATIVE FOR ParticleEmissionMaskDescriptor;
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 1) {
            unsigned int arg0;
            ok &= luaval_to_uint32(tolua_S, 2,&arg0, "cc.ParticleEmissionMaskCache:getEmissionMask");

            if (!ok) { break; }
            const cocos2d::ParticleEmissionMaskDescriptor& ret = cobj->getEmissionMask(arg0);
            #pragma warning NO CONVERSION FROM NATIVE FOR ParticleEmissionMaskDescriptor;
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "cc.ParticleEmissionMaskCache:getEmissionMask",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ParticleEmissionMaskCache_getEmissionMask'.",&tolua_err);
#endif

    return 0;
}

// Retained: existing unsupported layout/value stub.
int lua_cc_base_ParticleSystem_setHSVVar(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ParticleSystem* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ParticleSystem*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_ParticleSystem_setHSVVar'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::HSV arg0;

        #pragma warning NO CONVERSION TO NATIVE FOR HSV
		ok = false;
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ParticleSystem_setHSVVar'", nullptr);
            return 0;
        }
        cobj->setHSVVar(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:setHSVVar",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ParticleSystem_setHSVVar'.",&tolua_err);
#endif

    return 0;
}

// Retained: existing unsupported layout/value stub.
int lua_cc_base_ParticleSystem_setEmissionShape(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ParticleSystem* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ParticleSystem*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_ParticleSystem_setEmissionShape'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        unsigned short arg0;
        cocos2d::EmissionShape arg1;

        ok &= luaval_to_ushort(tolua_S, 2, &arg0, "cc.ParticleSystem:setEmissionShape");

        #pragma warning NO CONVERSION TO NATIVE FOR EmissionShape
		ok = false;
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ParticleSystem_setEmissionShape'", nullptr);
            return 0;
        }
        cobj->setEmissionShape(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:setEmissionShape",argc, 2);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ParticleSystem_setEmissionShape'.",&tolua_err);
#endif

    return 0;
}

// Retained: existing unsupported layout/value stub.
int lua_cc_base_ParticleSystem_getHSVVar(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ParticleSystem* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ParticleSystem*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_ParticleSystem_getHSVVar'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ParticleSystem_getHSVVar'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getHSVVar();
        #pragma warning NO CONVERSION FROM NATIVE FOR HSV;
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:getHSVVar",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ParticleSystem_getHSVVar'.",&tolua_err);
#endif

    return 0;
}

// Retained: existing unsupported layout/value stub.
int lua_cc_base_ParticleSystem_getHSV(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ParticleSystem* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ParticleSystem*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_ParticleSystem_getHSV'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ParticleSystem_getHSV'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getHSV();
        #pragma warning NO CONVERSION FROM NATIVE FOR HSV;
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:getHSV",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ParticleSystem_getHSV'.",&tolua_err);
#endif

    return 0;
}

// Retained: existing unsupported layout/value stub.
int lua_cc_base_ParticleSystem_addEmissionShape(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ParticleSystem* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ParticleSystem*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_ParticleSystem_addEmissionShape'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::EmissionShape arg0;

        #pragma warning NO CONVERSION TO NATIVE FOR EmissionShape
		ok = false;
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ParticleSystem_addEmissionShape'", nullptr);
            return 0;
        }
        cobj->addEmissionShape(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:addEmissionShape",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ParticleSystem_addEmissionShape'.",&tolua_err);
#endif

    return 0;
}

// Retained: existing unsupported layout/value stub.
int lua_cc_base_ParticleSystem_setHSV(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ParticleSystem* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ParticleSystem*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_ParticleSystem_setHSV'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::HSV arg0;

        #pragma warning NO CONVERSION TO NATIVE FOR HSV
		ok = false;
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ParticleSystem_setHSV'", nullptr);
            return 0;
        }
        cobj->setHSV(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:setHSV",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ParticleSystem_setHSV'.",&tolua_err);
#endif

    return 0;
}

// Retained: existing unsupported layout/value stub.
int lua_cc_base_ParticleSystem_createRectTorusShape(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.ParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 3)
    {
        cocos2d::Vec2 arg0;
        cocos2d::Size arg1;
        cocos2d::Size arg2;
        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.ParticleSystem:createRectTorusShape");
        ok &= luaval_to_size(tolua_S, 3, &arg1, "cc.ParticleSystem:createRectTorusShape");
        ok &= luaval_to_size(tolua_S, 4, &arg2, "cc.ParticleSystem:createRectTorusShape");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ParticleSystem_createRectTorusShape'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::ParticleSystem::createRectTorusShape(arg0, arg1, arg2);
        #pragma warning NO CONVERSION FROM NATIVE FOR EmissionShape;
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.ParticleSystem:createRectTorusShape",argc, 3);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ParticleSystem_createRectTorusShape'.",&tolua_err);
#endif
    return 0;
}

// Retained: existing unsupported layout/value stub.
int lua_cc_base_ParticleSystem_createTorusShape(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.ParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 3)
    {
        cocos2d::Vec2 arg0;
        double arg1;
        double arg2;
        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.ParticleSystem:createTorusShape");
        ok &= luaval_to_number(tolua_S, 3,&arg1, "cc.ParticleSystem:createTorusShape");
        ok &= luaval_to_number(tolua_S, 4,&arg2, "cc.ParticleSystem:createTorusShape");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ParticleSystem_createTorusShape'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::ParticleSystem::createTorusShape(arg0, arg1, arg2);
        #pragma warning NO CONVERSION FROM NATIVE FOR EmissionShape;
        return 1;
    }
    if (argc == 4)
    {
        cocos2d::Vec2 arg0;
        double arg1;
        double arg2;
        double arg3;
        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.ParticleSystem:createTorusShape");
        ok &= luaval_to_number(tolua_S, 3,&arg1, "cc.ParticleSystem:createTorusShape");
        ok &= luaval_to_number(tolua_S, 4,&arg2, "cc.ParticleSystem:createTorusShape");
        ok &= luaval_to_number(tolua_S, 5,&arg3, "cc.ParticleSystem:createTorusShape");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ParticleSystem_createTorusShape'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::ParticleSystem::createTorusShape(arg0, arg1, arg2, arg3);
        #pragma warning NO CONVERSION FROM NATIVE FOR EmissionShape;
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.ParticleSystem:createTorusShape",argc, 3);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ParticleSystem_createTorusShape'.",&tolua_err);
#endif
    return 0;
}

// Retained: existing unsupported layout/value stub.
int lua_cc_base_ParticleSystem_createConeShape(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.ParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 4)
    {
        cocos2d::Vec2 arg0;
        double arg1;
        double arg2;
        double arg3;
        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.ParticleSystem:createConeShape");
        ok &= luaval_to_number(tolua_S, 3,&arg1, "cc.ParticleSystem:createConeShape");
        ok &= luaval_to_number(tolua_S, 4,&arg2, "cc.ParticleSystem:createConeShape");
        ok &= luaval_to_number(tolua_S, 5,&arg3, "cc.ParticleSystem:createConeShape");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ParticleSystem_createConeShape'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::ParticleSystem::createConeShape(arg0, arg1, arg2, arg3);
        #pragma warning NO CONVERSION FROM NATIVE FOR EmissionShape;
        return 1;
    }
    if (argc == 5)
    {
        cocos2d::Vec2 arg0;
        double arg1;
        double arg2;
        double arg3;
        double arg4;
        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.ParticleSystem:createConeShape");
        ok &= luaval_to_number(tolua_S, 3,&arg1, "cc.ParticleSystem:createConeShape");
        ok &= luaval_to_number(tolua_S, 4,&arg2, "cc.ParticleSystem:createConeShape");
        ok &= luaval_to_number(tolua_S, 5,&arg3, "cc.ParticleSystem:createConeShape");
        ok &= luaval_to_number(tolua_S, 6,&arg4, "cc.ParticleSystem:createConeShape");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ParticleSystem_createConeShape'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::ParticleSystem::createConeShape(arg0, arg1, arg2, arg3, arg4);
        #pragma warning NO CONVERSION FROM NATIVE FOR EmissionShape;
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.ParticleSystem:createConeShape",argc, 4);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ParticleSystem_createConeShape'.",&tolua_err);
#endif
    return 0;
}

// Retained: existing unsupported layout/value stub.
int lua_cc_base_ParticleSystem_createPointShape(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.ParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        cocos2d::Vec2 arg0;
        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.ParticleSystem:createPointShape");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ParticleSystem_createPointShape'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::ParticleSystem::createPointShape(arg0);
        #pragma warning NO CONVERSION FROM NATIVE FOR EmissionShape;
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.ParticleSystem:createPointShape",argc, 1);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ParticleSystem_createPointShape'.",&tolua_err);
#endif
    return 0;
}

// Retained: existing unsupported layout/value stub.
int lua_cc_base_ParticleSystem_createCircleShape(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.ParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        cocos2d::Vec2 arg0;
        double arg1;
        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.ParticleSystem:createCircleShape");
        ok &= luaval_to_number(tolua_S, 3,&arg1, "cc.ParticleSystem:createCircleShape");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ParticleSystem_createCircleShape'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::ParticleSystem::createCircleShape(arg0, arg1);
        #pragma warning NO CONVERSION FROM NATIVE FOR EmissionShape;
        return 1;
    }
    if (argc == 3)
    {
        cocos2d::Vec2 arg0;
        double arg1;
        double arg2;
        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.ParticleSystem:createCircleShape");
        ok &= luaval_to_number(tolua_S, 3,&arg1, "cc.ParticleSystem:createCircleShape");
        ok &= luaval_to_number(tolua_S, 4,&arg2, "cc.ParticleSystem:createCircleShape");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ParticleSystem_createCircleShape'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::ParticleSystem::createCircleShape(arg0, arg1, arg2);
        #pragma warning NO CONVERSION FROM NATIVE FOR EmissionShape;
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.ParticleSystem:createCircleShape",argc, 2);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ParticleSystem_createCircleShape'.",&tolua_err);
#endif
    return 0;
}

// Retained: existing unsupported layout/value stub.
int lua_cc_base_ParticleSystem_createMaskShape(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.ParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::string_view arg0;
        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.ParticleSystem:createMaskShape");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ParticleSystem_createMaskShape'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::ParticleSystem::createMaskShape(arg0);
        #pragma warning NO CONVERSION FROM NATIVE FOR EmissionShape;
        return 1;
    }
    if (argc == 2)
    {
        std::string_view arg0;
        cocos2d::Vec2 arg1;
        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.ParticleSystem:createMaskShape");
        ok &= luaval_to_vec2(tolua_S, 3, &arg1, "cc.ParticleSystem:createMaskShape");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ParticleSystem_createMaskShape'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::ParticleSystem::createMaskShape(arg0, arg1);
        #pragma warning NO CONVERSION FROM NATIVE FOR EmissionShape;
        return 1;
    }
    if (argc == 3)
    {
        std::string_view arg0;
        cocos2d::Vec2 arg1;
        cocos2d::Vec2 arg2;
        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.ParticleSystem:createMaskShape");
        ok &= luaval_to_vec2(tolua_S, 3, &arg1, "cc.ParticleSystem:createMaskShape");
        ok &= luaval_to_vec2(tolua_S, 4, &arg2, "cc.ParticleSystem:createMaskShape");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ParticleSystem_createMaskShape'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::ParticleSystem::createMaskShape(arg0, arg1, arg2);
        #pragma warning NO CONVERSION FROM NATIVE FOR EmissionShape;
        return 1;
    }
    if (argc == 4)
    {
        std::string_view arg0;
        cocos2d::Vec2 arg1;
        cocos2d::Vec2 arg2;
        cocos2d::Vec2 arg3;
        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.ParticleSystem:createMaskShape");
        ok &= luaval_to_vec2(tolua_S, 3, &arg1, "cc.ParticleSystem:createMaskShape");
        ok &= luaval_to_vec2(tolua_S, 4, &arg2, "cc.ParticleSystem:createMaskShape");
        ok &= luaval_to_vec2(tolua_S, 5, &arg3, "cc.ParticleSystem:createMaskShape");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ParticleSystem_createMaskShape'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::ParticleSystem::createMaskShape(arg0, arg1, arg2, arg3);
        #pragma warning NO CONVERSION FROM NATIVE FOR EmissionShape;
        return 1;
    }
    if (argc == 5)
    {
        std::string_view arg0;
        cocos2d::Vec2 arg1;
        cocos2d::Vec2 arg2;
        cocos2d::Vec2 arg3;
        double arg4;
        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.ParticleSystem:createMaskShape");
        ok &= luaval_to_vec2(tolua_S, 3, &arg1, "cc.ParticleSystem:createMaskShape");
        ok &= luaval_to_vec2(tolua_S, 4, &arg2, "cc.ParticleSystem:createMaskShape");
        ok &= luaval_to_vec2(tolua_S, 5, &arg3, "cc.ParticleSystem:createMaskShape");
        ok &= luaval_to_number(tolua_S, 6,&arg4, "cc.ParticleSystem:createMaskShape");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ParticleSystem_createMaskShape'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::ParticleSystem::createMaskShape(arg0, arg1, arg2, arg3, arg4);
        #pragma warning NO CONVERSION FROM NATIVE FOR EmissionShape;
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.ParticleSystem:createMaskShape",argc, 1);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ParticleSystem_createMaskShape'.",&tolua_err);
#endif
    return 0;
}

// Retained: existing unsupported layout/value stub.
int lua_cc_base_ParticleSystem_createRectShape(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.ParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        cocos2d::Vec2 arg0;
        cocos2d::Size arg1;
        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.ParticleSystem:createRectShape");
        ok &= luaval_to_size(tolua_S, 3, &arg1, "cc.ParticleSystem:createRectShape");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ParticleSystem_createRectShape'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::ParticleSystem::createRectShape(arg0, arg1);
        #pragma warning NO CONVERSION FROM NATIVE FOR EmissionShape;
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.ParticleSystem:createRectShape",argc, 2);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ParticleSystem_createRectShape'.",&tolua_err);
#endif
    return 0;
}

// Retained: existing unsupported layout/value stub.
int lua_cc_base_ParticleSystem_createConeTorusShape(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.ParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 5)
    {
        cocos2d::Vec2 arg0;
        double arg1;
        double arg2;
        double arg3;
        double arg4;
        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.ParticleSystem:createConeTorusShape");
        ok &= luaval_to_number(tolua_S, 3,&arg1, "cc.ParticleSystem:createConeTorusShape");
        ok &= luaval_to_number(tolua_S, 4,&arg2, "cc.ParticleSystem:createConeTorusShape");
        ok &= luaval_to_number(tolua_S, 5,&arg3, "cc.ParticleSystem:createConeTorusShape");
        ok &= luaval_to_number(tolua_S, 6,&arg4, "cc.ParticleSystem:createConeTorusShape");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ParticleSystem_createConeTorusShape'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::ParticleSystem::createConeTorusShape(arg0, arg1, arg2, arg3, arg4);
        #pragma warning NO CONVERSION FROM NATIVE FOR EmissionShape;
        return 1;
    }
    if (argc == 6)
    {
        cocos2d::Vec2 arg0;
        double arg1;
        double arg2;
        double arg3;
        double arg4;
        double arg5;
        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.ParticleSystem:createConeTorusShape");
        ok &= luaval_to_number(tolua_S, 3,&arg1, "cc.ParticleSystem:createConeTorusShape");
        ok &= luaval_to_number(tolua_S, 4,&arg2, "cc.ParticleSystem:createConeTorusShape");
        ok &= luaval_to_number(tolua_S, 5,&arg3, "cc.ParticleSystem:createConeTorusShape");
        ok &= luaval_to_number(tolua_S, 6,&arg4, "cc.ParticleSystem:createConeTorusShape");
        ok &= luaval_to_number(tolua_S, 7,&arg5, "cc.ParticleSystem:createConeTorusShape");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ParticleSystem_createConeTorusShape'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::ParticleSystem::createConeTorusShape(arg0, arg1, arg2, arg3, arg4, arg5);
        #pragma warning NO CONVERSION FROM NATIVE FOR EmissionShape;
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.ParticleSystem:createConeTorusShape",argc, 5);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ParticleSystem_createConeTorusShape'.",&tolua_err);
#endif
    return 0;
}

// Retained: existing unsupported layout/value stub.
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

// Retained: existing unsupported layout/value stub.
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

// Retained: existing unsupported layout/value stub.
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

// Retained: existing unsupported layout/value stub.
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

// Retained: existing unsupported layout/value stub.
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

// Retained: existing unsupported layout/value stub.
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

// Retained: existing unsupported layout/value stub.
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

// Retained: existing unsupported layout/value stub.
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

// Retained: existing unsupported layout/value stub.
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

// Retained: existing unsupported layout/value stub.
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

// Retained: existing unsupported layout/value stub.
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

// Retained: existing unsupported layout/value stub.
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

// Retained: existing unsupported layout/value stub.
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

// Retained: existing unsupported layout/value stub.
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

// Retained: existing unsupported layout/value stub.
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

// Retained: existing unsupported layout/value stub.
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

// Retained: existing unsupported layout/value stub.
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

// Retained: existing unsupported layout/value stub.
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

// Retained: existing unsupported layout/value stub.
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

// Retained: existing unsupported layout/value stub.
int lua_cc_base_ComponentLua_getScriptObject(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ComponentLua* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ComponentLua",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ComponentLua*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_ComponentLua_getScriptObject'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ComponentLua_getScriptObject'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getScriptObject();
        #pragma warning NO CONVERSION FROM NATIVE FOR void*;
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ComponentLua:getScriptObject",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ComponentLua_getScriptObject'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_GLViewImpl_create(lua_State* lua_S)
{
    LUA_SINVOKE_HEADER("cc.GLViewImpl", "cc.GLViewImpl:create");
    LUA_TRY_INVOKE_R(1, ([](std::string_view name) { return cocos2d::GLViewImpl::create(name); }));
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM == CC_PLATFORM_MAC || CC_TARGET_PLATFORM == CC_PLATFORM_LINUX
    LUA_TRY_INVOKE_R(2, ([](std::string_view name, bool resizable) { return cocos2d::GLViewImpl::create(name, resizable); }));
#endif
    LUA_SINVOKE_FOOTER("1,2");
}
int lua_cc_base_GLViewImpl_createWithRect(lua_State* lua_S)
{
    LUA_SINVOKE_HEADER("cc.GLViewImpl", "cc.GLViewImpl:createWithRect");
    LUA_TRY_INVOKE_R(2, ([](std::string_view name, cocos2d::Rect rect) { return cocos2d::GLViewImpl::createWithRect(name, rect); }));
    LUA_TRY_INVOKE_R(3, ([](std::string_view name, cocos2d::Rect rect, float zoom) { return cocos2d::GLViewImpl::createWithRect(name, rect, zoom); }));
    LUA_TRY_INVOKE_R(4, ([](std::string_view name, cocos2d::Rect rect, float zoom, bool resizable) { return cocos2d::GLViewImpl::createWithRect(name, rect, zoom, resizable); }));
    LUA_SINVOKE_FOOTER("2,3,4");
}

#if CC_TARGET_PLATFORM != CC_PLATFORM_WIN32
int lua_register_cc_base_EventListenerController(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EventListenerController, "EventListenerController", "cc.EventListenerController", cocos2d::EventListener, "cc.EventListener", nullptr, nullptr);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_base_EventController_getControllerEventType(lua_State* lua_S)
{
    LUA_INVOKE_HEADER("cc.EventController", "cc.EventController:getControllerEventType");
    LUA_TRY_INVOKE_R(0, static_cast<cocos2d::EventController::ControllerEventType(cocos2d::EventController::*)()const>(&cocos2d::EventController::getControllerEventType));
    LUA_INVOKE_FOOTER("0");
}

int lua_cc_base_EventController_setConnectStatus(lua_State* lua_S)
{
    LUA_INVOKE_HEADER("cc.EventController", "cc.EventController:setConnectStatus");
    LUA_TRY_INVOKE(1, static_cast<void(cocos2d::EventController::*)(bool)>(&cocos2d::EventController::setConnectStatus));
    LUA_INVOKE_FOOTER("1");
}

int lua_cc_base_EventController_isConnected(lua_State* lua_S)
{
    LUA_INVOKE_HEADER("cc.EventController", "cc.EventController:isConnected");
    LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::EventController::*)()const>(&cocos2d::EventController::isConnected));
    LUA_INVOKE_FOOTER("0");
}

int lua_cc_base_EventController_setKeyCode(lua_State* lua_S)
{
    LUA_INVOKE_HEADER("cc.EventController", "cc.EventController:setKeyCode");
    LUA_TRY_INVOKE(1, static_cast<void(cocos2d::EventController::*)(int)>(&cocos2d::EventController::setKeyCode));
    LUA_INVOKE_FOOTER("1");
}

int lua_cc_base_EventController_getController(lua_State* lua_S)
{
    LUA_INVOKE_HEADER("cc.EventController", "cc.EventController:getController");
    LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Controller*(cocos2d::EventController::*)()const>(&cocos2d::EventController::getController));
    LUA_INVOKE_FOOTER("0");
}

int lua_cc_base_EventController_getKeyCode(lua_State* lua_S)
{
    LUA_INVOKE_HEADER("cc.EventController", "cc.EventController:getKeyCode");
    LUA_TRY_INVOKE_R(0, static_cast<int(cocos2d::EventController::*)()const>(&cocos2d::EventController::getKeyCode));
    LUA_INVOKE_FOOTER("0");
}

int lua_register_cc_base_EventController(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EventController, "EventController", "cc.EventController", cocos2d::Event, "cc.Event", nullptr, nullptr);
	LUA_METHOD("getControllerEventType", lua_cc_base_EventController_getControllerEventType);
	LUA_METHOD("setConnectStatus", lua_cc_base_EventController_setConnectStatus);
	LUA_METHOD("isConnected", lua_cc_base_EventController_isConnected);
	LUA_METHOD("setKeyCode", lua_cc_base_EventController_setKeyCode);
	LUA_METHOD("getController", lua_cc_base_EventController_getController);
	LUA_METHOD("getKeyCode", lua_cc_base_EventController_getKeyCode);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
#endif

int lua_cc_base_Node_removeFromParentAndCleanup(lua_State* lua_S)
{
    LUA_INVOKE_HEADER("cc.Node", "cc.Node:removeFromParent");
    LUA_TRY_INVOKE(0, static_cast<void(cocos2d::Node::*)()>(&cocos2d::Node::removeFromParent));
    LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Node::*)(bool)>(&cocos2d::Node::removeFromParentAndCleanup));
    LUA_INVOKE_FOOTER("0,1");
}
int lua_cc_base_Node_removeAllChildrenWithCleanup(lua_State* lua_S)
{
    LUA_INVOKE_HEADER("cc.Node", "cc.Node:removeAllChildren");
    LUA_TRY_INVOKE(0, static_cast<void(cocos2d::Node::*)()>(&cocos2d::Node::removeAllChildren));
    LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Node::*)(bool)>(&cocos2d::Node::removeAllChildrenWithCleanup));
    LUA_INVOKE_FOOTER("0,1");
}

// Retained: unsupported PixelBufferDescriptor callback layout.
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

#if (CC_USE_PHYSICS || (CC_USE_3D_PHYSICS && CC_ENABLE_BULLET_INTEGRATION))
int lua_cc_base_Scene_initPhysicsWorld(lua_State* lua_S)
{
    LUA_INVOKE_HEADER("cc.Scene", "cc.Scene:initPhysicsWorld");
    LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::Scene::*)()>(&cocos2d::Scene::initPhysicsWorld));
    LUA_INVOKE_FOOTER("0");
}
#endif
#if (CC_USE_PHYSICS || (CC_USE_3D_PHYSICS && CC_ENABLE_BULLET_INTEGRATION))
int lua_cc_base_Scene_initWithPhysics(lua_State* lua_S)
{
    LUA_INVOKE_HEADER("cc.Scene", "cc.Scene:initWithPhysics");
    LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::Scene::*)()>(&cocos2d::Scene::initWithPhysics));
    LUA_INVOKE_FOOTER("0");
}
#endif
#if (CC_USE_PHYSICS || (CC_USE_3D_PHYSICS && CC_ENABLE_BULLET_INTEGRATION))
int lua_cc_base_Scene_createWithPhysics(lua_State* lua_S)
{
    LUA_SINVOKE_HEADER("cc.Scene", "cc.Scene:createWithPhysics");
    LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Scene*(*)()>(&cocos2d::Scene::createWithPhysics));
    LUA_SINVOKE_FOOTER("0");
}
#endif
#if (CC_USE_PHYSICS || (CC_USE_3D_PHYSICS && CC_ENABLE_BULLET_INTEGRATION) || CC_USE_NAVMESH)
int lua_cc_base_Scene_stepPhysicsAndNavigation(lua_State* lua_S)
{
    LUA_INVOKE_HEADER("cc.Scene", "cc.Scene:stepPhysicsAndNavigation");
    LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Scene::*)(float)>(&cocos2d::Scene::stepPhysicsAndNavigation));
    LUA_INVOKE_FOOTER("1");
}
#endif

int register_all_cc_base_retained(lua_State* L)
{
    luaL_getmetatable(L, "cc.Node");
    if (lua_istable(L, -1)) {
        tolua_function(L, "removeFromParent", lua_cc_base_Node_removeFromParentAndCleanup);
        tolua_function(L, "removeAllChildren", lua_cc_base_Node_removeAllChildrenWithCleanup);
    }
    lua_pop(L, 1);
#if CC_TARGET_PLATFORM != CC_PLATFORM_WIN32
	lua_register_cc_base_EventListenerController(L);
	lua_register_cc_base_EventController(L);
#endif
	luaL_getmetatable(L, "cc.Texture2D");
	if (lua_istable(L, -1)) {
		tolua_function(L, "updateWithMipmaps", lua_cc_base_Texture2D_updateWithMipmaps);
		tolua_function(L, "updateTextureDescriptor", lua_cc_base_Texture2D_updateTextureDescriptor);
		tolua_function(L, "updateWithSubData", lua_cc_base_Texture2D_updateWithSubData);
	}
	lua_pop(L, 1);
	luaL_getmetatable(L, "cc.Node");
	if (lua_istable(L, -1)) {
#if CC_USE_PHYSICS
		tolua_function(L, "setPhysicsBody", lua_cc_base_Node_setPhysicsBody);
#endif
#if CC_USE_PHYSICS
		tolua_function(L, "getPhysicsBody", lua_cc_base_Node_getPhysicsBody);
#endif
	}
	lua_pop(L, 1);
	luaL_getmetatable(L, "cc.Scene");
	if (lua_istable(L, -1)) {
#if (CC_USE_PHYSICS || (CC_USE_3D_PHYSICS && CC_ENABLE_BULLET_INTEGRATION))
        tolua_function(L, "initPhysicsWorld", lua_cc_base_Scene_initPhysicsWorld);
#endif
#if (CC_USE_PHYSICS || (CC_USE_3D_PHYSICS && CC_ENABLE_BULLET_INTEGRATION))
        tolua_function(L, "initWithPhysics", lua_cc_base_Scene_initWithPhysics);
#endif
#if (CC_USE_PHYSICS || (CC_USE_3D_PHYSICS && CC_ENABLE_BULLET_INTEGRATION))
        tolua_function(L, "createWithPhysics", lua_cc_base_Scene_createWithPhysics);
#endif
#if (CC_USE_PHYSICS || (CC_USE_3D_PHYSICS && CC_ENABLE_BULLET_INTEGRATION) || CC_USE_NAVMESH)
        tolua_function(L, "stepPhysicsAndNavigation", lua_cc_base_Scene_stepPhysicsAndNavigation);
#endif

		tolua_function(L, "render", lua_cc_base_Scene_render);
#if CC_USE_PHYSICS
		tolua_function(L, "getPhysicsWorld", lua_cc_base_Scene_getPhysicsWorld);
#endif
	}
	lua_pop(L, 1);
	luaL_getmetatable(L, "cc.GLView");
	if (lua_istable(L, -1)) {
		tolua_function(L, "setGLContextAttrs", lua_cc_base_GLView_setGLContextAttrs);
		tolua_function(L, "getGLContextAttrs", lua_cc_base_GLView_getGLContextAttrs);
	}
	lua_pop(L, 1);
	luaL_getmetatable(L, "cc.AsyncTaskPool");
	if (lua_istable(L, -1)) {
		tolua_function(L, "enqueue", lua_cc_base_AsyncTaskPool_enqueue);
	}
	lua_pop(L, 1);
	luaL_getmetatable(L, "cc.BezierBy");
	if (lua_istable(L, -1)) {
		tolua_function(L, "initWithDuration", lua_cc_base_BezierBy_initWithDuration);
	}
	lua_pop(L, 1);
	luaL_getmetatable(L, "cc.BezierTo");
	if (lua_istable(L, -1)) {
		tolua_function(L, "initWithDuration", lua_cc_base_BezierTo_initWithDuration);
	}
	lua_pop(L, 1);
	luaL_getmetatable(L, "cc.FileUtils");
	if (lua_istable(L, -1)) {
		tolua_function(L, "writeBinaryToFile", lua_cc_base_FileUtils_writeBinaryToFile);
	}
	lua_pop(L, 1);
	luaL_getmetatable(L, "cc.EventDispatcher");
	if (lua_istable(L, -1)) {
		tolua_function(L, "dispatchCustomEvent", lua_cc_base_EventDispatcher_dispatchCustomEvent);
	}
	lua_pop(L, 1);
	luaL_getmetatable(L, "cc.ParticleEmissionMaskCache");
	if (lua_istable(L, -1)) {
		tolua_function(L, "getEmissionMask", lua_cc_base_ParticleEmissionMaskCache_getEmissionMask);
	}
	lua_pop(L, 1);
	luaL_getmetatable(L, "cc.ParticleSystem");
	if (lua_istable(L, -1)) {
		tolua_function(L, "setHSVVar", lua_cc_base_ParticleSystem_setHSVVar);
		tolua_function(L, "setEmissionShape", lua_cc_base_ParticleSystem_setEmissionShape);
		tolua_function(L, "getHSVVar", lua_cc_base_ParticleSystem_getHSVVar);
		tolua_function(L, "getHSV", lua_cc_base_ParticleSystem_getHSV);
		tolua_function(L, "addEmissionShape", lua_cc_base_ParticleSystem_addEmissionShape);
		tolua_function(L, "setHSV", lua_cc_base_ParticleSystem_setHSV);
		tolua_function(L, "createRectTorusShape", lua_cc_base_ParticleSystem_createRectTorusShape);
		tolua_function(L, "createTorusShape", lua_cc_base_ParticleSystem_createTorusShape);
		tolua_function(L, "createConeShape", lua_cc_base_ParticleSystem_createConeShape);
		tolua_function(L, "createPointShape", lua_cc_base_ParticleSystem_createPointShape);
		tolua_function(L, "createCircleShape", lua_cc_base_ParticleSystem_createCircleShape);
		tolua_function(L, "createMaskShape", lua_cc_base_ParticleSystem_createMaskShape);
		tolua_function(L, "createRectShape", lua_cc_base_ParticleSystem_createRectShape);
		tolua_function(L, "createConeTorusShape", lua_cc_base_ParticleSystem_createConeTorusShape);
	}
	lua_pop(L, 1);
	luaL_getmetatable(L, "cc.Pass");
	if (lua_istable(L, -1)) {
		tolua_function(L, "setUniformPointLightPosition", lua_cc_base_Pass_setUniformPointLightPosition);
		tolua_function(L, "setUniformDirLightDir", lua_cc_base_Pass_setUniformDirLightDir);
		tolua_function(L, "setUniformSpotLightOuterAngleCos", lua_cc_base_Pass_setUniformSpotLightOuterAngleCos);
		tolua_function(L, "setUniformSpotLightDir", lua_cc_base_Pass_setUniformSpotLightDir);
		tolua_function(L, "setUniformMatrixPalette", lua_cc_base_Pass_setUniformMatrixPalette);
		tolua_function(L, "setUniformSpotLightRangeInverse", lua_cc_base_Pass_setUniformSpotLightRangeInverse);
		tolua_function(L, "setUniformPointLightRangeInverse", lua_cc_base_Pass_setUniformPointLightRangeInverse);
		tolua_function(L, "setUniformSpotLightColor", lua_cc_base_Pass_setUniformSpotLightColor);
		tolua_function(L, "setUniformAmbientLigthColor", lua_cc_base_Pass_setUniformAmbientLigthColor);
		tolua_function(L, "setUniformDirLightColor", lua_cc_base_Pass_setUniformDirLightColor);
		tolua_function(L, "setUniformSpotLightPosition", lua_cc_base_Pass_setUniformSpotLightPosition);
		tolua_function(L, "setUniformSpotLightInnerAngleCos", lua_cc_base_Pass_setUniformSpotLightInnerAngleCos);
		tolua_function(L, "setUniformColor", lua_cc_base_Pass_setUniformColor);
		tolua_function(L, "setUniformPointLightColor", lua_cc_base_Pass_setUniformPointLightColor);
	}
	lua_pop(L, 1);
	luaL_getmetatable(L, "cc.Renderer");
	if (lua_istable(L, -1)) {
        tolua_function(L, "readPixels", lua_cc_base_Renderer_readPixels);
		tolua_function(L, "setDepthStencilDesc", lua_cc_base_Renderer_setDepthStencilDesc);
		tolua_function(L, "getViewport", lua_cc_base_Renderer_getViewport);
		tolua_function(L, "getDepthStencilDesc", lua_cc_base_Renderer_getDepthStencilDesc);
		tolua_function(L, "getScissorRect", lua_cc_base_Renderer_getScissorRect);
	}
	lua_pop(L, 1);
	luaL_getmetatable(L, "cc.TMXTileAnimTask");
	if (lua_istable(L, -1)) {
		tolua_function(L, "create", lua_cc_base_TMXTileAnimTask_create);
	}
	lua_pop(L, 1);
	luaL_getmetatable(L, "cc.ComponentLua");
	if (lua_istable(L, -1)) {
		tolua_function(L, "getScriptObject", lua_cc_base_ComponentLua_getScriptObject);
	}
	lua_pop(L, 1);
	luaL_getmetatable(L, "cc.GLViewImpl");
	if (lua_istable(L, -1)) {
		tolua_function(L, "create", lua_cc_base_GLViewImpl_create);
		tolua_function(L, "createWithRect", lua_cc_base_GLViewImpl_createWithRect);
	}
	lua_pop(L, 1);
	return 0;
}
