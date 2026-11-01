#include "scripting/lua-bindings/auto/cclua_3d_auto.hpp"
#include "cocos2d.h"
#include "3d/CCBundle3D.h"
#include "scripting/lua-bindings/manual/tolua_fix.h"
#include "scripting/lua-bindings/manual/LuaBasicConversions.h"


#include "cclua_3d_compat.hpp"
namespace core_3d_binding
{
struct Error { const char* name; const char* native; const char* format; const char* label; int expected; bool invalid; };
static const Error errors[] = {
        {"cc.Animation3D:initWithFile", "lua_cc_3d_Animation3D_initWithFile", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Animation3D:initWithFile", 2, true},
        {"cc.Animation3D:getDuration", "lua_cc_3d_Animation3D_getDuration", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Animation3D:getDuration", 0, true},
        {"cc.Animation3D:create", "lua_cc_3d_Animation3D_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.Animation3D:create", 1, true},
        {"cc.Animate3D:getSpeed", "lua_cc_3d_Animate3D_getSpeed", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Animate3D:getSpeed", 0, true},
        {"cc.Animate3D:setQuality", "lua_cc_3d_Animate3D_setQuality", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Animate3D:setQuality", 1, true},
        {"cc.Animate3D:setWeight", "lua_cc_3d_Animate3D_setWeight", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Animate3D:setWeight", 1, true},
        {"cc.Animate3D:removeFromMap", "lua_cc_3d_Animate3D_removeFromMap", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Animate3D:removeFromMap", 0, true},
        {"cc.Animate3D:initWithFrames", "lua_cc_3d_Animate3D_initWithFrames", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Animate3D:initWithFrames", 4, true},
        {"cc.Animate3D:getOriginInterval", "lua_cc_3d_Animate3D_getOriginInterval", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Animate3D:getOriginInterval", 0, true},
        {"cc.Animate3D:setSpeed", "lua_cc_3d_Animate3D_setSpeed", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Animate3D:setSpeed", 1, true},
        {"cc.Animate3D:init", "lua_cc_3d_Animate3D_init", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Animate3D:init", 1, false},
        {"cc.Animate3D:setOriginInterval", "lua_cc_3d_Animate3D_setOriginInterval", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Animate3D:setOriginInterval", 1, true},
        {"cc.Animate3D:getWeight", "lua_cc_3d_Animate3D_getWeight", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Animate3D:getWeight", 0, true},
        {"cc.Animate3D:getQuality", "lua_cc_3d_Animate3D_getQuality", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Animate3D:getQuality", 0, true},
        {"cc.Animate3D:create", "lua_cc_3d_Animate3D_create", "%s has wrong number of arguments: %d, was expecting %d", "cc.Animate3D:create", 1, false},
        {"cc.Animate3D:getTransitionTime", "lua_cc_3d_Animate3D_getTransitionTime", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.Animate3D:getTransitionTime", 0, true},
        {"cc.Animate3D:createWithFrames", "lua_cc_3d_Animate3D_createWithFrames", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.Animate3D:createWithFrames", 3, true},
        {"cc.Animate3D:setTransitionTime", "lua_cc_3d_Animate3D_setTransitionTime", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.Animate3D:setTransitionTime", 1, true},
        {"cc.TextureCube:getBackendTexture", "lua_cc_3d_TextureCube_getBackendTexture", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TextureCube:getBackendTexture", 0, true},
        {"cc.TextureCube:reloadTexture", "lua_cc_3d_TextureCube_reloadTexture", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TextureCube:reloadTexture", 0, true},
        {"cc.TextureCube:create", "lua_cc_3d_TextureCube_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.TextureCube:create", 6, true},
        {"cc.BillBoard:getMode", "lua_cc_3d_BillBoard_getMode", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.BillBoard:getMode", 0, true},
        {"cc.BillBoard:setMode", "lua_cc_3d_BillBoard_setMode", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.BillBoard:setMode", 1, true},
        {"cc.BillBoard:createWithTexture", "lua_cc_3d_BillBoard_createWithTexture", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.BillBoard:createWithTexture", 1, true},
        {"cc.Mesh:getVertexSizeInBytes", "lua_cc_3d_Mesh_getVertexSizeInBytes", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Mesh:getVertexSizeInBytes", 0, true},
        {"cc.Mesh:setProgramState", "lua_cc_3d_Mesh_setProgramState", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Mesh:setProgramState", 1, true},
        {"cc.Mesh:setIndexFormat", "lua_cc_3d_Mesh_setIndexFormat", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Mesh:setIndexFormat", 1, true},
        {"cc.Mesh:getName", "lua_cc_3d_Mesh_getName", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Mesh:getName", 0, true},
        {"cc.Mesh:calculateAABB", "lua_cc_3d_Mesh_calculateAABB", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Mesh:calculateAABB", 0, true},
        {"cc.Mesh:setName", "lua_cc_3d_Mesh_setName", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Mesh:setName", 1, true},
        {"cc.Mesh:getMeshVertexAttribCount", "lua_cc_3d_Mesh_getMeshVertexAttribCount", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Mesh:getMeshVertexAttribCount", 0, true},
        {"cc.Mesh:isVisible", "lua_cc_3d_Mesh_isVisible", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Mesh:isVisible", 0, true},
        {"cc.Mesh:setVisible", "lua_cc_3d_Mesh_setVisible", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Mesh:setVisible", 1, true},
        {"cc.Skeleton3D:removeAllBones", "lua_cc_3d_Skeleton3D_removeAllBones", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Skeleton3D:removeAllBones", 0, true},
        {"cc.Skeleton3D:updateBoneMatrix", "lua_cc_3d_Skeleton3D_updateBoneMatrix", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Skeleton3D:updateBoneMatrix", 0, true},
        {"cc.Skeleton3D:getRootCount", "lua_cc_3d_Skeleton3D_getRootCount", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Skeleton3D:getRootCount", 0, true},
        {"cc.Skeleton3D:getBoneCount", "lua_cc_3d_Skeleton3D_getBoneCount", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Skeleton3D:getBoneCount", 0, true},
        {"cc.Skybox:reload", "lua_cc_3d_Skybox_reload", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Skybox:reload", 0, true},
        {"cc.Skybox:setTexture", "lua_cc_3d_Skybox_setTexture", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Skybox:setTexture", 1, true},
        {"cc.Skybox:create", "lua_cc_3d_Skybox_create", "%s has wrong number of arguments: %d, was expecting %d", "cc.Skybox:create", 0, false},
        {"cc.MeshRenderer:setCullFaceEnabled", "lua_cc_3d_MeshRenderer_setCullFaceEnabled", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.MeshRenderer:setCullFaceEnabled", 1, true},
        {"cc.MeshRenderer:getLightMask", "lua_cc_3d_MeshRenderer_getLightMask", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.MeshRenderer:getLightMask", 0, true},
        {"cc.MeshRenderer:setWireframe", "lua_cc_3d_MeshRenderer_setWireframe", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.MeshRenderer:setWireframe", 1, true},
        {"cc.MeshRenderer:isWireframe", "lua_cc_3d_MeshRenderer_isWireframe", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.MeshRenderer:isWireframe", 0, true},
        {"cc.MeshRenderer:setCullFace", "lua_cc_3d_MeshRenderer_setCullFace", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.MeshRenderer:setCullFace", 1, true},
        {"cc.MeshRenderer:removeAllAttachNode", "lua_cc_3d_MeshRenderer_removeAllAttachNode", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.MeshRenderer:removeAllAttachNode", 0, true},
        {"cc.MeshRenderer:getMeshCount", "lua_cc_3d_MeshRenderer_getMeshCount", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.MeshRenderer:getMeshCount", 0, true},
        {"cc.MeshRenderer:getMeshByIndex", "lua_cc_3d_MeshRenderer_getMeshByIndex", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.MeshRenderer:getMeshByIndex", 1, true},
        {"cc.MeshRenderer:isForceDepthWrite", "lua_cc_3d_MeshRenderer_isForceDepthWrite", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.MeshRenderer:isForceDepthWrite", 0, true},
        {"cc.MeshRenderer:setLightMask", "lua_cc_3d_MeshRenderer_setLightMask", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.MeshRenderer:setLightMask", 1, true},
        {"cc.MeshRenderer:getAttachNode", "lua_cc_3d_MeshRenderer_getAttachNode", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.MeshRenderer:getAttachNode", 1, true},
        {"cc.MeshRenderer:genMaterial", "lua_cc_3d_MeshRenderer_genMaterial", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.MeshRenderer:genMaterial", 0, true},
        {"cc.MeshRenderer:removeAttachNode", "lua_cc_3d_MeshRenderer_removeAttachNode", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.MeshRenderer:removeAttachNode", 1, true},
        {"cc.MeshRenderer:setForceDepthWrite", "lua_cc_3d_MeshRenderer_setForceDepthWrite", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.MeshRenderer:setForceDepthWrite", 1, true},
        {"cc.MeshRendererCache:removeAllMeshRenderData", "lua_cc_3d_MeshRendererCache_removeAllMeshRenderData", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.MeshRendererCache:removeAllMeshRenderData", 0, true},
        {"cc.MeshRendererCache:removeMeshRenderData", "lua_cc_3d_MeshRendererCache_removeMeshRenderData", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.MeshRendererCache:removeMeshRenderData", 1, true},
        {"cc.MeshMaterial:getMaterialType", "lua_cc_3d_MeshMaterial_getMaterialType", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.MeshMaterial:getMaterialType", 0, true},
        {"cc.MeshMaterial:createWithFilename", "lua_cc_3d_MeshMaterial_createWithFilename", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.MeshMaterial:createWithFilename", 1, true},
        {"cc.MeshMaterial:releaseCachedMaterial", "lua_cc_3d_MeshMaterial_releaseCachedMaterial", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.MeshMaterial:releaseCachedMaterial", 0, true},
        {"cc.MeshMaterial:createBuiltInMaterial", "lua_cc_3d_MeshMaterial_createBuiltInMaterial", "%s has wrong number of arguments: %d, was expecting %d", "cc.MeshMaterial:createBuiltInMaterial", 2, false},
        {"cc.MeshMaterial:releaseBuiltInMaterial", "lua_cc_3d_MeshMaterial_releaseBuiltInMaterial", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.MeshMaterial:releaseBuiltInMaterial", 0, true},
        {"cc.MeshMaterial:createWithProgramState", "lua_cc_3d_MeshMaterial_createWithProgramState", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.MeshMaterial:createWithProgramState", 1, true},
        {"cc.Terrain:initHeightMap", "lua_cc_3d_Terrain_initHeightMap", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Terrain:initHeightMap", 1, true},
        {"cc.Terrain:setMaxDetailMapAmount", "lua_cc_3d_Terrain_setMaxDetailMapAmount", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Terrain:setMaxDetailMapAmount", 1, true},
        {"cc.Terrain:setDrawWire", "lua_cc_3d_Terrain_setDrawWire", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Terrain:setDrawWire", 1, true},
        {"cc.Terrain:resetHeightMap", "lua_cc_3d_Terrain_resetHeightMap", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Terrain:resetHeightMap", 1, true},
        {"cc.Terrain:setAlphaMap", "lua_cc_3d_Terrain_setAlphaMap", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Terrain:setAlphaMap", 1, true},
        {"cc.Terrain:setSkirtHeightRatio", "lua_cc_3d_Terrain_setSkirtHeightRatio", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Terrain:setSkirtHeightRatio", 1, true},
        {"cc.Terrain:initTextures", "lua_cc_3d_Terrain_initTextures", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Terrain:initTextures", 0, true},
        {"cc.Terrain:initProperties", "lua_cc_3d_Terrain_initProperties", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Terrain:initProperties", 0, true},
        {"cc.Terrain:setLODDistance", "lua_cc_3d_Terrain_setLODDistance", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Terrain:setLODDistance", 3, true},
        {"cc.Terrain:reload", "lua_cc_3d_Terrain_reload", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Terrain:reload", 0, true},
        {"cc.Terrain:getImageHeight", "lua_cc_3d_Terrain_getImageHeight", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Terrain:getImageHeight", 2, true},
        {"cc.Terrain:setLightMap", "lua_cc_3d_Terrain_setLightMap", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Terrain:setLightMap", 1, true},
        {"cc.Terrain:setIsEnableFrustumCull", "lua_cc_3d_Terrain_setIsEnableFrustumCull", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Terrain:setIsEnableFrustumCull", 1, true},
        {"cc.Terrain:getMinHeight", "lua_cc_3d_Terrain_getMinHeight", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Terrain:getMinHeight", 0, true},
        {"cc.Terrain:getMaxHeight", "lua_cc_3d_Terrain_getMaxHeight", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Terrain:getMaxHeight", 0, true},
        {"cc.Bundle3D:load", "lua_cc_3d_Bundle3D_load", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Bundle3D:load", 1, true},
        {"cc.Bundle3D:clear", "lua_cc_3d_Bundle3D_clear", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Bundle3D:clear", 0, true},
        {"cc.Bundle3D:parseSamplerAddressMode", "lua_cc_3d_Bundle3D_parseSamplerAddressMode", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.Bundle3D:parseSamplerAddressMode", 1, true},
        {"cc.Bundle3D:destroyBundle", "lua_cc_3d_Bundle3D_destroyBundle", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.Bundle3D:destroyBundle", 1, true},
        {"cc.Bundle3D:parseGLDataType", "lua_cc_3d_Bundle3D_parseGLDataType", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.Bundle3D:parseGLDataType", 2, true},
};
const char* parent_name(const char* type)
{
    struct Parent { const char* type; const char* parent; };
    static const Parent parents[] = {
        {"cc.Animation3D", "cc.Ref"},
        {"cc.Animate3D", "cc.ActionInterval"},
        {"cc.TextureCube", "cc.Ref"},
        {"cc.AttachNode", "cc.Node"},
        {"cc.BillBoard", "cc.Sprite"},
        {"cc.Mesh", "cc.Ref"},
        {"cc.Skeleton3D", "cc.Ref"},
        {"cc.Skybox", "cc.Node"},
        {"cc.MeshRenderer", "cc.Node"},
        {"cc.MeshRendererCache", ""},
        {"cc.MeshMaterial", "cc.Material"},
        {"cc.Terrain", "cc.Node"},
        {"cc.Bundle3D", ""},
    };
    for (const auto& p : parents) if (std::strcmp(type,p.type)==0) return p.parent;
    return "";
}
const char* native_symbol(const char* name)
{
    for (const auto& e : errors) if (std::strcmp(name,e.name)==0) return e.native;
    return name;
}
void check_receiver(lua_State* L,const char* type,const char* name,bool member)
{
#if CC_DEBUG >= 1
    tolua_Error error{};
    const bool valid=member ? tolua_isusertype(L,1,type,0,&error) : tolua_isusertable(L,1,type,0,&error);
    if (!valid) {
        char text[256]; std::snprintf(text,sizeof(text),"#ferror in function '%s'.",native_symbol(name));
        tolua_error(L,text,&error);
    }
    if (member && !tolua_tousertype(L,1,nullptr)) {
        char text[256]; std::snprintf(text,sizeof(text),"invalid 'cobj' in function '%s'",native_symbol(name));
        tolua_error(L,text,nullptr);
    }
#else
    (void)L; (void)type; (void)name; (void)member;
#endif
}
int fail(lua_State* L,const char* name,int argc,int attempted)
{
    for (const auto& e : errors) if (std::strcmp(name,e.name)==0) {
        if (attempted!=-1 && e.invalid) {
            char text[256]; std::snprintf(text,sizeof(text),"invalid arguments in function '%s'",e.native);
            tolua_error(L,text,nullptr); return 0;
        }
        return luaL_error(L,e.format,e.label,argc,e.expected);
    }
    return luaL_error(L,"unmapped Core binding: %s",name);
}
}
int lua_cc_3d_Animation3D_constructor(lua_State* tolua_S);
int lua_cc_3d_Animation3D_init(lua_State* tolua_S);
int lua_cc_3d_Animate3D_constructor(lua_State* tolua_S);
int lua_cc_3d_Animate3D_setKeyFrameUserInfo(lua_State* tolua_S);
int lua_cc_3d_TextureCube_constructor(lua_State* tolua_S);
int lua_cc_3d_TextureCube_getImagePaths(lua_State* tolua_S);
int lua_cc_3d_TextureCube_setTexParameters(lua_State* tolua_S);
int lua_cc_3d_AttachNode_constructor(lua_State* tolua_S);
int lua_cc_3d_AttachNode_create(lua_State* tolua_S);
int lua_cc_3d_BillBoard_constructor(lua_State* tolua_S);
int lua_cc_3d_BillBoard_create(lua_State* tolua_S);
int lua_cc_3d_Mesh_constructor(lua_State* tolua_S);
int lua_cc_3d_Mesh_getMaterial(lua_State* tolua_S);
int lua_cc_3d_Mesh_setMaterial(lua_State* tolua_S);
int lua_cc_3d_Mesh_getMeshVertexAttribute(lua_State* tolua_S);
int lua_cc_3d_Mesh_draw(lua_State* tolua_S);
int lua_cc_3d_Mesh_getBlendFunc(lua_State* tolua_S);
int lua_cc_3d_Mesh_setMeshIndexData(lua_State* tolua_S);
int lua_cc_3d_Mesh_getProgramState(lua_State* tolua_S);
int lua_cc_3d_Mesh_setBlendFunc(lua_State* tolua_S);
int lua_cc_3d_Mesh_setSkin(lua_State* tolua_S);
int lua_cc_3d_Skeleton3D_constructor(lua_State* tolua_S);
int lua_cc_3d_Skeleton3D_addBone(lua_State* tolua_S);
int lua_cc_3d_Skeleton3D_getBoneByName(lua_State* tolua_S);
int lua_cc_3d_Skeleton3D_getRootBone(lua_State* tolua_S);
int lua_cc_3d_Skeleton3D_getBoneByIndex(lua_State* tolua_S);
int lua_cc_3d_Skeleton3D_getBoneIndex(lua_State* tolua_S);
int lua_cc_3d_Skybox_constructor(lua_State* tolua_S);
int lua_cc_3d_Skybox_init(lua_State* tolua_S);
int lua_cc_3d_MeshRenderer_setTexture(lua_State* tolua_S);
int lua_cc_3d_MeshRenderer_getMaterial(lua_State* tolua_S);
int lua_cc_3d_MeshRenderer_getMeshes(lua_State* tolua_S);
int lua_cc_3d_MeshRenderer_setMaterial(lua_State* tolua_S);
int lua_cc_3d_MeshRenderer_getMesh(lua_State* tolua_S);
int lua_cc_3d_MeshRenderer_getBlendFunc(lua_State* tolua_S);
int lua_cc_3d_MeshRenderer_setBlendFunc(lua_State* tolua_S);
int lua_cc_3d_MeshRenderer_getSkeleton(lua_State* tolua_S);
int lua_cc_3d_MeshRenderer_getMeshByName(lua_State* tolua_S);
int lua_cc_3d_MeshRenderer_create(lua_State* tolua_S);
int lua_cc_3d_MeshRendererCache_constructor(lua_State* tolua_S);
int lua_cc_3d_MeshRendererCache_destroyInstance(lua_State* tolua_S);
int lua_cc_3d_MeshRendererCache_getInstance(lua_State* tolua_S);
int lua_cc_3d_Terrain_constructor(lua_State* tolua_S);
int lua_cc_3d_Terrain_getHeightData(lua_State* tolua_S);
int lua_cc_3d_Terrain_setDetailMap(lua_State* tolua_S);
int lua_cc_3d_Terrain_setLightDir(lua_State* tolua_S);
int lua_cc_3d_Terrain_convertToTerrainSpace(lua_State* tolua_S);
int lua_cc_3d_Terrain_initWithTerrainData(lua_State* tolua_S);
int lua_cc_3d_Terrain_getTerrainSize(lua_State* tolua_S);
int lua_cc_3d_Terrain_getNormal(lua_State* tolua_S);
int lua_cc_3d_Bundle3D_constructor(lua_State* tolua_S);
int lua_cc_3d_Bundle3D_loadSkinData(lua_State* tolua_S);
int lua_cc_3d_Bundle3D_loadMaterials(lua_State* tolua_S);
int lua_cc_3d_Bundle3D_loadNodes(lua_State* tolua_S);
int lua_cc_3d_Bundle3D_loadAnimationData(lua_State* tolua_S);
int lua_cc_3d_Bundle3D_createBundle(lua_State* tolua_S);

int register_all_cc_3d_retained(lua_State* L)
{
    luaL_getmetatable(L,"cc.Animation3D");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_3d_Animation3D_constructor);
        tolua_function(L,"init",lua_cc_3d_Animation3D_init);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.Animate3D");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_3d_Animate3D_constructor);
        tolua_function(L,"setKeyFrameUserInfo",lua_cc_3d_Animate3D_setKeyFrameUserInfo);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.TextureCube");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_3d_TextureCube_constructor);
        tolua_function(L,"getImagePaths",lua_cc_3d_TextureCube_getImagePaths);
        tolua_function(L,"setTexParameters",lua_cc_3d_TextureCube_setTexParameters);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.AttachNode");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_3d_AttachNode_constructor);
        tolua_function(L,"create",lua_cc_3d_AttachNode_create);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.BillBoard");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_3d_BillBoard_constructor);
        tolua_function(L,"create",lua_cc_3d_BillBoard_create);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.Mesh");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_3d_Mesh_constructor);
        tolua_function(L,"getMaterial",lua_cc_3d_Mesh_getMaterial);
        tolua_function(L,"setMaterial",lua_cc_3d_Mesh_setMaterial);
        tolua_function(L,"getMeshVertexAttribute",lua_cc_3d_Mesh_getMeshVertexAttribute);
        tolua_function(L,"draw",lua_cc_3d_Mesh_draw);
        tolua_function(L,"getBlendFunc",lua_cc_3d_Mesh_getBlendFunc);
        tolua_function(L,"setMeshIndexData",lua_cc_3d_Mesh_setMeshIndexData);
        tolua_function(L,"getProgramState",lua_cc_3d_Mesh_getProgramState);
        tolua_function(L,"setBlendFunc",lua_cc_3d_Mesh_setBlendFunc);
        tolua_function(L,"setSkin",lua_cc_3d_Mesh_setSkin);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.Skeleton3D");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_3d_Skeleton3D_constructor);
        tolua_function(L,"addBone",lua_cc_3d_Skeleton3D_addBone);
        tolua_function(L,"getBoneByName",lua_cc_3d_Skeleton3D_getBoneByName);
        tolua_function(L,"getRootBone",lua_cc_3d_Skeleton3D_getRootBone);
        tolua_function(L,"getBoneByIndex",lua_cc_3d_Skeleton3D_getBoneByIndex);
        tolua_function(L,"getBoneIndex",lua_cc_3d_Skeleton3D_getBoneIndex);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.Skybox");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_3d_Skybox_constructor);
        tolua_function(L,"init",lua_cc_3d_Skybox_init);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.MeshRenderer");
    if (lua_istable(L,-1)) {
        tolua_function(L,"setTexture",lua_cc_3d_MeshRenderer_setTexture);
        tolua_function(L,"getMaterial",lua_cc_3d_MeshRenderer_getMaterial);
        tolua_function(L,"getMeshes",lua_cc_3d_MeshRenderer_getMeshes);
        tolua_function(L,"setMaterial",lua_cc_3d_MeshRenderer_setMaterial);
        tolua_function(L,"getMesh",lua_cc_3d_MeshRenderer_getMesh);
        tolua_function(L,"getBlendFunc",lua_cc_3d_MeshRenderer_getBlendFunc);
        tolua_function(L,"setBlendFunc",lua_cc_3d_MeshRenderer_setBlendFunc);
        tolua_function(L,"getSkeleton",lua_cc_3d_MeshRenderer_getSkeleton);
        tolua_function(L,"getMeshByName",lua_cc_3d_MeshRenderer_getMeshByName);
        tolua_function(L,"create",lua_cc_3d_MeshRenderer_create);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.MeshRendererCache");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_3d_MeshRendererCache_constructor);
        tolua_function(L,"destroyInstance",lua_cc_3d_MeshRendererCache_destroyInstance);
        tolua_function(L,"getInstance",lua_cc_3d_MeshRendererCache_getInstance);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.Terrain");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_3d_Terrain_constructor);
        tolua_function(L,"getHeightData",lua_cc_3d_Terrain_getHeightData);
        tolua_function(L,"setDetailMap",lua_cc_3d_Terrain_setDetailMap);
        tolua_function(L,"setLightDir",lua_cc_3d_Terrain_setLightDir);
        tolua_function(L,"convertToTerrainSpace",lua_cc_3d_Terrain_convertToTerrainSpace);
        tolua_function(L,"initWithTerrainData",lua_cc_3d_Terrain_initWithTerrainData);
        tolua_function(L,"getTerrainSize",lua_cc_3d_Terrain_getTerrainSize);
        tolua_function(L,"getNormal",lua_cc_3d_Terrain_getNormal);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.Bundle3D");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_3d_Bundle3D_constructor);
        tolua_function(L,"loadSkinData",lua_cc_3d_Bundle3D_loadSkinData);
        tolua_function(L,"loadMaterials",lua_cc_3d_Bundle3D_loadMaterials);
        tolua_function(L,"loadNodes",lua_cc_3d_Bundle3D_loadNodes);
        tolua_function(L,"loadAnimationData",lua_cc_3d_Bundle3D_loadAnimationData);
        tolua_function(L,"createBundle",lua_cc_3d_Bundle3D_createBundle);
    }
    lua_pop(L,1);
    return 0;
}
