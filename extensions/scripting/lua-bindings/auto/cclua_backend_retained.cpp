#include "scripting/lua-bindings/auto/cclua_backend_auto.hpp"
#include "renderer/backend/Types.h"
#include "renderer/backend/ProgramState.h"
#include "renderer/backend/Texture.h"
#include "renderer/backend/VertexLayout.h"
#include "renderer/backend/Device.h"
#include "renderer/backend/RenderTarget.h"
#include "scripting/lua-bindings/manual/tolua_fix.h"
#include "scripting/lua-bindings/manual/LuaBasicConversions.h"



#include "cclua_backend_compat.hpp"
namespace core_backend_binding
{
struct Error { const char* name; const char* native; const char* format; const char* label; int expected; bool invalid; };
static const Error errors[] = {
        {"ccb.Program:getMaxVertexLocation", "lua_cc_backend_Program_getMaxVertexLocation", "%s has wrong number of arguments: %d, was expecting %d \n", "ccb.Program:getMaxVertexLocation", 0, true},
        {"ccb.Program:getMaxFragmentLocation", "lua_cc_backend_Program_getMaxFragmentLocation", "%s has wrong number of arguments: %d, was expecting %d \n", "ccb.Program:getMaxFragmentLocation", 0, true},
        {"ccb.Program:setProgramType", "lua_cc_backend_Program_setProgramType", "%s has wrong number of arguments: %d, was expecting %d \n", "ccb.Program:setProgramType", 1, true},
        {"ccb.Program:getFragmentShader", "lua_cc_backend_Program_getFragmentShader", "%s has wrong number of arguments: %d, was expecting %d \n", "ccb.Program:getFragmentShader", 0, true},
        {"ccb.Program:getUniformBufferSize", "lua_cc_backend_Program_getUniformBufferSize", "%s has wrong number of arguments: %d, was expecting %d \n", "ccb.Program:getUniformBufferSize", 1, true},
        {"ccb.Program:getProgramType", "lua_cc_backend_Program_getProgramType", "%s has wrong number of arguments: %d, was expecting %d \n", "ccb.Program:getProgramType", 0, true},
        {"ccb.Program:getVertexShader", "lua_cc_backend_Program_getVertexShader", "%s has wrong number of arguments: %d, was expecting %d \n", "ccb.Program:getVertexShader", 0, true},
        {"ccb.Program:getBuiltinProgram", "lua_cc_backend_Program_getBuiltinProgram", "%s has wrong number of arguments: %d, was expecting %d\n ", "ccb.Program:getBuiltinProgram", 1, true},
        {"ccb.VertexLayout:getVertexStepMode", "lua_cc_backend_VertexLayout_getVertexStepMode", "%s has wrong number of arguments: %d, was expecting %d \n", "ccb.VertexLayout:getVertexStepMode", 0, true},
        {"ccb.VertexLayout:isValid", "lua_cc_backend_VertexLayout_isValid", "%s has wrong number of arguments: %d, was expecting %d \n", "ccb.VertexLayout:isValid", 0, true},
        {"ccb.VertexLayout:getStride", "lua_cc_backend_VertexLayout_getStride", "%s has wrong number of arguments: %d, was expecting %d \n", "ccb.VertexLayout:getStride", 0, true},
        {"ccb.ProgramState:updateUniformID", "lua_cc_backend_ProgramState_updateUniformID", "%s has wrong number of arguments: %d, was expecting %d \n", "ccb.ProgramState:updateUniformID", 0, true},
        {"ccb.ProgramState:getProgram", "lua_cc_backend_ProgramState_getProgram", "%s has wrong number of arguments: %d, was expecting %d \n", "ccb.ProgramState:getProgram", 0, true},
        {"ccb.ProgramState:setParameterAutoBinding", "lua_cc_backend_ProgramState_setParameterAutoBinding", "%s has wrong number of arguments: %d, was expecting %d \n", "ccb.ProgramState:setParameterAutoBinding", 2, true},
        {"ccb.ProgramState:setVertexStride", "lua_cc_backend_ProgramState_setVertexStride", "%s has wrong number of arguments: %d, was expecting %d \n", "ccb.ProgramState:setVertexStride", 1, true},
        {"ccb.ProgramState:clone", "lua_cc_backend_ProgramState_clone", "%s has wrong number of arguments: %d, was expecting %d \n", "ccb.ProgramState:clone", 0, true},
        {"ccb.ProgramState:getUniformID", "lua_cc_backend_ProgramState_getUniformID", "%s has wrong number of arguments: %d, was expecting %d \n", "ccb.ProgramState:getUniformID", 0, true},
        {"ccb.TextureBackend:getTextureFormat", "lua_cc_backend_TextureBackend_getTextureFormat", "%s has wrong number of arguments: %d, was expecting %d \n", "ccb.TextureBackend:getTextureFormat", 0, true},
        {"ccb.TextureBackend:generateMipmaps", "lua_cc_backend_TextureBackend_generateMipmaps", "%s has wrong number of arguments: %d, was expecting %d \n", "ccb.TextureBackend:generateMipmaps", 0, true},
        {"ccb.TextureBackend:getHeight", "lua_cc_backend_TextureBackend_getHeight", "%s has wrong number of arguments: %d, was expecting %d \n", "ccb.TextureBackend:getHeight", 0, true},
        {"ccb.TextureBackend:getTextureUsage", "lua_cc_backend_TextureBackend_getTextureUsage", "%s has wrong number of arguments: %d, was expecting %d \n", "ccb.TextureBackend:getTextureUsage", 0, true},
        {"ccb.TextureBackend:getWidth", "lua_cc_backend_TextureBackend_getWidth", "%s has wrong number of arguments: %d, was expecting %d \n", "ccb.TextureBackend:getWidth", 0, true},
        {"ccb.TextureBackend:hasMipmaps", "lua_cc_backend_TextureBackend_hasMipmaps", "%s has wrong number of arguments: %d, was expecting %d \n", "ccb.TextureBackend:hasMipmaps", 0, true},
        {"ccb.TextureBackend:getCount", "lua_cc_backend_TextureBackend_getCount", "%s has wrong number of arguments: %d, was expecting %d \n", "ccb.TextureBackend:getCount", 0, true},
        {"ccb.TextureBackend:getHandler", "lua_cc_backend_TextureBackend_getHandler", "%s has wrong number of arguments: %d, was expecting %d \n", "ccb.TextureBackend:getHandler", 0, true},
        {"ccb.TextureBackend:getTextureType", "lua_cc_backend_TextureBackend_getTextureType", "%s has wrong number of arguments: %d, was expecting %d \n", "ccb.TextureBackend:getTextureType", 0, true},
        {"ccb.Device:newProgram", "lua_cc_backend_Device_newProgram", "%s has wrong number of arguments: %d, was expecting %d \n", "ccb.Device:newProgram", 2, true},
        {"ccb.Device:getInstance", "lua_cc_backend_Device_getInstance", "%s has wrong number of arguments: %d, was expecting %d\n ", "ccb.Device:getInstance", 0, true},
};
const char* parent_name(const char* type)
{
    struct Parent { const char* type; const char* parent; };
    static const Parent parents[] = {
        {"ccb.Program", "cc.Ref"},
        {"ccb.VertexLayout", ""},
        {"ccb.ProgramState", "cc.Ref"},
        {"ccb.TextureBackend", "cc.Ref"},
        {"ccb.Texture2DBackend", "ccb.TextureBackend"},
        {"ccb.TextureCubemapBackend", "ccb.TextureBackend"},
        {"ccb.Device", "cc.Ref"},
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

int lua_register_cc_backend_BufferUsage(lua_State* tolua_S)
{
    tolua_module(tolua_S, "BufferUsage", 0);
    tolua_beginmodule(tolua_S,"BufferUsage");
        tolua_constant(tolua_S, "STATIC", 0);
        tolua_constant(tolua_S, "DYNAMIC", 1);
    tolua_endmodule(tolua_S);

    auto typeName = typeid(cocos2d::backend::BufferUsage).name(); // rtti is literal storage
    g_luaType[reinterpret_cast<uintptr_t>(typeName)] = "ccb.BufferUsage";
    g_typeCast[typeName] = "ccb.BufferUsage";
    return 1;
}

int lua_register_cc_backend_BufferType(lua_State* tolua_S)
{
    tolua_module(tolua_S, "BufferType", 0);
    tolua_beginmodule(tolua_S,"BufferType");
        tolua_constant(tolua_S, "VERTEX", 0);
        tolua_constant(tolua_S, "INDEX", 1);
    tolua_endmodule(tolua_S);

    auto typeName = typeid(cocos2d::backend::BufferType).name(); // rtti is literal storage
    g_luaType[reinterpret_cast<uintptr_t>(typeName)] = "ccb.BufferType";
    g_typeCast[typeName] = "ccb.BufferType";
    return 1;
}

int lua_register_cc_backend_ShaderStage(lua_State* tolua_S)
{
    tolua_module(tolua_S, "ShaderStage", 0);
    tolua_beginmodule(tolua_S,"ShaderStage");
        tolua_constant(tolua_S, "VERTEX", 0);
        tolua_constant(tolua_S, "FRAGMENT", 1);
        tolua_constant(tolua_S, "VERTEX_AND_FRAGMENT", 2);
    tolua_endmodule(tolua_S);

    auto typeName = typeid(cocos2d::backend::ShaderStage).name(); // rtti is literal storage
    g_luaType[reinterpret_cast<uintptr_t>(typeName)] = "ccb.ShaderStage";
    g_typeCast[typeName] = "ccb.ShaderStage";
    return 1;
}

int lua_register_cc_backend_VertexFormat(lua_State* tolua_S)
{
    tolua_module(tolua_S, "VertexFormat", 0);
    tolua_beginmodule(tolua_S,"VertexFormat");
        tolua_constant(tolua_S, "FLOAT4", 0);
        tolua_constant(tolua_S, "FLOAT3", 1);
        tolua_constant(tolua_S, "FLOAT2", 2);
        tolua_constant(tolua_S, "FLOAT", 3);
        tolua_constant(tolua_S, "INT4", 4);
        tolua_constant(tolua_S, "INT3", 5);
        tolua_constant(tolua_S, "INT2", 6);
        tolua_constant(tolua_S, "INT", 7);
        tolua_constant(tolua_S, "USHORT4", 8);
        tolua_constant(tolua_S, "USHORT2", 9);
        tolua_constant(tolua_S, "UBYTE4", 10);
    tolua_endmodule(tolua_S);

    auto typeName = typeid(cocos2d::backend::VertexFormat).name(); // rtti is literal storage
    g_luaType[reinterpret_cast<uintptr_t>(typeName)] = "ccb.VertexFormat";
    g_typeCast[typeName] = "ccb.VertexFormat";
    return 1;
}

int lua_register_cc_backend_PixelFormat(lua_State* tolua_S)
{
    tolua_module(tolua_S, "PixelFormat", 0);
    tolua_beginmodule(tolua_S,"PixelFormat");
        tolua_constant(tolua_S, "PVRTC4", 0);
        tolua_constant(tolua_S, "PVRTC4A", 1);
        tolua_constant(tolua_S, "PVRTC2", 2);
        tolua_constant(tolua_S, "PVRTC2A", 3);
        tolua_constant(tolua_S, "ETC1", 4);
        tolua_constant(tolua_S, "ETC2_RGB", 5);
        tolua_constant(tolua_S, "ETC2_RGBA", 6);
        tolua_constant(tolua_S, "S3TC_DXT1", 7);
        tolua_constant(tolua_S, "S3TC_DXT3", 8);
        tolua_constant(tolua_S, "S3TC_DXT5", 9);
        tolua_constant(tolua_S, "ATC_RGB", 10);
        tolua_constant(tolua_S, "ATC_EXPLICIT_ALPHA", 11);
        tolua_constant(tolua_S, "ATC_INTERPOLATED_ALPHA", 12);
        tolua_constant(tolua_S, "ASTC4x4", 13);
        tolua_constant(tolua_S, "ASTC5x5", 14);
        tolua_constant(tolua_S, "ASTC6x6", 15);
        tolua_constant(tolua_S, "ASTC8x5", 16);
        tolua_constant(tolua_S, "ASTC8x6", 17);
        tolua_constant(tolua_S, "ASTC8x8", 18);
        tolua_constant(tolua_S, "ASTC10x5", 19);
        tolua_constant(tolua_S, "RGBA8", 20);
        tolua_constant(tolua_S, "BGRA8", 21);
        tolua_constant(tolua_S, "RGB8", 22);
        tolua_constant(tolua_S, "RGB565", 23);
        tolua_constant(tolua_S, "RGBA4", 24);
        tolua_constant(tolua_S, "RGB5A1", 25);
        tolua_constant(tolua_S, "A8", 26);
        tolua_constant(tolua_S, "L8", 27);
        tolua_constant(tolua_S, "LA8", 28);
        tolua_constant(tolua_S, "D24S8", 29);
        tolua_constant(tolua_S, "COUNT", 30);
        tolua_constant(tolua_S, "NONE", 65535);
    tolua_endmodule(tolua_S);

    auto typeName = typeid(cocos2d::backend::PixelFormat).name(); // rtti is literal storage
    g_luaType[reinterpret_cast<uintptr_t>(typeName)] = "ccb.PixelFormat";
    g_typeCast[typeName] = "ccb.PixelFormat";
    return 1;
}

int lua_register_cc_backend_TextureUsage(lua_State* tolua_S)
{
    tolua_module(tolua_S, "TextureUsage", 0);
    tolua_beginmodule(tolua_S,"TextureUsage");
        tolua_constant(tolua_S, "READ", 0);
        tolua_constant(tolua_S, "WRITE", 1);
        tolua_constant(tolua_S, "RENDER_TARGET", 2);
    tolua_endmodule(tolua_S);

    auto typeName = typeid(cocos2d::backend::TextureUsage).name(); // rtti is literal storage
    g_luaType[reinterpret_cast<uintptr_t>(typeName)] = "ccb.TextureUsage";
    g_typeCast[typeName] = "ccb.TextureUsage";
    return 1;
}

int lua_register_cc_backend_IndexFormat(lua_State* tolua_S)
{
    tolua_module(tolua_S, "IndexFormat", 0);
    tolua_beginmodule(tolua_S,"IndexFormat");
        tolua_constant(tolua_S, "U_SHORT", 1);
        tolua_constant(tolua_S, "U_INT", 2);
    tolua_endmodule(tolua_S);

    auto typeName = typeid(cocos2d::backend::IndexFormat).name(); // rtti is literal storage
    g_luaType[reinterpret_cast<uintptr_t>(typeName)] = "ccb.IndexFormat";
    g_typeCast[typeName] = "ccb.IndexFormat";
    return 1;
}

int lua_register_cc_backend_VertexStepMode(lua_State* tolua_S)
{
    tolua_module(tolua_S, "VertexStepMode", 0);
    tolua_beginmodule(tolua_S,"VertexStepMode");
        tolua_constant(tolua_S, "VERTEX", 0);
        tolua_constant(tolua_S, "INSTANCE", 1);
    tolua_endmodule(tolua_S);

    auto typeName = typeid(cocos2d::backend::VertexStepMode).name(); // rtti is literal storage
    g_luaType[reinterpret_cast<uintptr_t>(typeName)] = "ccb.VertexStepMode";
    g_typeCast[typeName] = "ccb.VertexStepMode";
    return 1;
}

int lua_register_cc_backend_PrimitiveType(lua_State* tolua_S)
{
    tolua_module(tolua_S, "PrimitiveType", 0);
    tolua_beginmodule(tolua_S,"PrimitiveType");
        tolua_constant(tolua_S, "POINT", 0);
        tolua_constant(tolua_S, "LINE", 1);
        tolua_constant(tolua_S, "LINE_LOOP", 2);
        tolua_constant(tolua_S, "LINE_STRIP", 3);
        tolua_constant(tolua_S, "TRIANGLE", 4);
        tolua_constant(tolua_S, "TRIANGLE_STRIP", 5);
    tolua_endmodule(tolua_S);

    auto typeName = typeid(cocos2d::backend::PrimitiveType).name(); // rtti is literal storage
    g_luaType[reinterpret_cast<uintptr_t>(typeName)] = "ccb.PrimitiveType";
    g_typeCast[typeName] = "ccb.PrimitiveType";
    return 1;
}

int lua_register_cc_backend_TextureType(lua_State* tolua_S)
{
    tolua_module(tolua_S, "TextureType", 0);
    tolua_beginmodule(tolua_S,"TextureType");
        tolua_constant(tolua_S, "TEXTURE_2D", 0);
        tolua_constant(tolua_S, "TEXTURE_CUBE", 1);
    tolua_endmodule(tolua_S);

    auto typeName = typeid(cocos2d::backend::TextureType).name(); // rtti is literal storage
    g_luaType[reinterpret_cast<uintptr_t>(typeName)] = "ccb.TextureType";
    g_typeCast[typeName] = "ccb.TextureType";
    return 1;
}

int lua_register_cc_backend_SamplerAddressMode(lua_State* tolua_S)
{
    tolua_module(tolua_S, "SamplerAddressMode", 0);
    tolua_beginmodule(tolua_S,"SamplerAddressMode");
        tolua_constant(tolua_S, "REPEAT", 0);
        tolua_constant(tolua_S, "MIRROR_REPEAT", 1);
        tolua_constant(tolua_S, "CLAMP_TO_EDGE", 2);
        tolua_constant(tolua_S, "DONT_CARE", 3);
    tolua_endmodule(tolua_S);

    auto typeName = typeid(cocos2d::backend::SamplerAddressMode).name(); // rtti is literal storage
    g_luaType[reinterpret_cast<uintptr_t>(typeName)] = "ccb.SamplerAddressMode";
    g_typeCast[typeName] = "ccb.SamplerAddressMode";
    return 1;
}

int lua_register_cc_backend_SamplerFilter(lua_State* tolua_S)
{
    tolua_module(tolua_S, "SamplerFilter", 0);
    tolua_beginmodule(tolua_S,"SamplerFilter");
        tolua_constant(tolua_S, "NEAREST", 0);
        tolua_constant(tolua_S, "NEAREST_MIPMAP_NEAREST", 1);
        tolua_constant(tolua_S, "NEAREST_MIPMAP_LINEAR", 2);
        tolua_constant(tolua_S, "LINEAR", 3);
        tolua_constant(tolua_S, "LINEAR_MIPMAP_LINEAR", 4);
        tolua_constant(tolua_S, "LINEAR_MIPMAP_NEAREST", 5);
        tolua_constant(tolua_S, "DONT_CARE", 6);
    tolua_endmodule(tolua_S);

    auto typeName = typeid(cocos2d::backend::SamplerFilter).name(); // rtti is literal storage
    g_luaType[reinterpret_cast<uintptr_t>(typeName)] = "ccb.SamplerFilter";
    g_typeCast[typeName] = "ccb.SamplerFilter";
    return 1;
}

int lua_register_cc_backend_StencilOperation(lua_State* tolua_S)
{
    tolua_module(tolua_S, "StencilOperation", 0);
    tolua_beginmodule(tolua_S,"StencilOperation");
        tolua_constant(tolua_S, "KEEP", 0);
        tolua_constant(tolua_S, "ZERO", 1);
        tolua_constant(tolua_S, "REPLACE", 2);
        tolua_constant(tolua_S, "INVERT", 3);
        tolua_constant(tolua_S, "INCREMENT_WRAP", 4);
        tolua_constant(tolua_S, "DECREMENT_WRAP", 5);
    tolua_endmodule(tolua_S);

    auto typeName = typeid(cocos2d::backend::StencilOperation).name(); // rtti is literal storage
    g_luaType[reinterpret_cast<uintptr_t>(typeName)] = "ccb.StencilOperation";
    g_typeCast[typeName] = "ccb.StencilOperation";
    return 1;
}

int lua_register_cc_backend_CompareFunction(lua_State* tolua_S)
{
    tolua_module(tolua_S, "CompareFunction", 0);
    tolua_beginmodule(tolua_S,"CompareFunction");
        tolua_constant(tolua_S, "NEVER", 0);
        tolua_constant(tolua_S, "LESS", 1);
        tolua_constant(tolua_S, "LESS_EQUAL", 2);
        tolua_constant(tolua_S, "GREATER", 3);
        tolua_constant(tolua_S, "GREATER_EQUAL", 4);
        tolua_constant(tolua_S, "EQUAL", 5);
        tolua_constant(tolua_S, "NOT_EQUAL", 6);
        tolua_constant(tolua_S, "ALWAYS", 7);
    tolua_endmodule(tolua_S);

    auto typeName = typeid(cocos2d::backend::CompareFunction).name(); // rtti is literal storage
    g_luaType[reinterpret_cast<uintptr_t>(typeName)] = "ccb.CompareFunction";
    g_typeCast[typeName] = "ccb.CompareFunction";
    return 1;
}

int lua_register_cc_backend_BlendOperation(lua_State* tolua_S)
{
    tolua_module(tolua_S, "BlendOperation", 0);
    tolua_beginmodule(tolua_S,"BlendOperation");
        tolua_constant(tolua_S, "ADD", 0);
        tolua_constant(tolua_S, "SUBTRACT", 1);
        tolua_constant(tolua_S, "RESERVE_SUBTRACT", 2);
    tolua_endmodule(tolua_S);

    auto typeName = typeid(cocos2d::backend::BlendOperation).name(); // rtti is literal storage
    g_luaType[reinterpret_cast<uintptr_t>(typeName)] = "ccb.BlendOperation";
    g_typeCast[typeName] = "ccb.BlendOperation";
    return 1;
}

int lua_register_cc_backend_BlendFactor(lua_State* tolua_S)
{
    tolua_module(tolua_S, "BlendFactor", 0);
    tolua_beginmodule(tolua_S,"BlendFactor");
        tolua_constant(tolua_S, "ZERO", 0);
        tolua_constant(tolua_S, "ONE", 1);
        tolua_constant(tolua_S, "SRC_COLOR", 2);
        tolua_constant(tolua_S, "ONE_MINUS_SRC_COLOR", 3);
        tolua_constant(tolua_S, "SRC_ALPHA", 4);
        tolua_constant(tolua_S, "ONE_MINUS_SRC_ALPHA", 5);
        tolua_constant(tolua_S, "DST_COLOR", 6);
        tolua_constant(tolua_S, "ONE_MINUS_DST_COLOR", 7);
        tolua_constant(tolua_S, "DST_ALPHA", 8);
        tolua_constant(tolua_S, "ONE_MINUS_DST_ALPHA", 9);
        tolua_constant(tolua_S, "CONSTANT_ALPHA", 10);
        tolua_constant(tolua_S, "SRC_ALPHA_SATURATE", 11);
        tolua_constant(tolua_S, "ONE_MINUS_CONSTANT_ALPHA", 12);
        tolua_constant(tolua_S, "BLEND_CLOLOR", 13);
    tolua_endmodule(tolua_S);

    auto typeName = typeid(cocos2d::backend::BlendFactor).name(); // rtti is literal storage
    g_luaType[reinterpret_cast<uintptr_t>(typeName)] = "ccb.BlendFactor";
    g_typeCast[typeName] = "ccb.BlendFactor";
    return 1;
}

int lua_register_cc_backend_ColorWriteMask(lua_State* tolua_S)
{
    tolua_module(tolua_S, "ColorWriteMask", 0);
    tolua_beginmodule(tolua_S,"ColorWriteMask");
        tolua_constant(tolua_S, "RED_BIT", 0);
        tolua_constant(tolua_S, "GREEN_BIT", 1);
        tolua_constant(tolua_S, "BLUE_BIT", 2);
        tolua_constant(tolua_S, "ALPHA_BIT", 3);
        tolua_constant(tolua_S, "NONE", 0);
        tolua_constant(tolua_S, "RED", 1);
        tolua_constant(tolua_S, "GREEN", 2);
        tolua_constant(tolua_S, "BLUE", 4);
        tolua_constant(tolua_S, "ALPHA", 8);
        tolua_constant(tolua_S, "ALL", 15);
    tolua_endmodule(tolua_S);

    auto typeName = typeid(cocos2d::backend::ColorWriteMask).name(); // rtti is literal storage
    g_luaType[reinterpret_cast<uintptr_t>(typeName)] = "ccb.ColorWriteMask";
    g_typeCast[typeName] = "ccb.ColorWriteMask";
    return 1;
}

int lua_register_cc_backend_CullMode(lua_State* tolua_S)
{
    tolua_module(tolua_S, "CullMode", 0);
    tolua_beginmodule(tolua_S,"CullMode");
        tolua_constant(tolua_S, "NONE", 0);
        tolua_constant(tolua_S, "BACK", 1);
        tolua_constant(tolua_S, "FRONT", 2);
    tolua_endmodule(tolua_S);

    auto typeName = typeid(cocos2d::backend::CullMode).name(); // rtti is literal storage
    g_luaType[reinterpret_cast<uintptr_t>(typeName)] = "ccb.CullMode";
    g_typeCast[typeName] = "ccb.CullMode";
    return 1;
}

int lua_register_cc_backend_Winding(lua_State* tolua_S)
{
    tolua_module(tolua_S, "Winding", 0);
    tolua_beginmodule(tolua_S,"Winding");
        tolua_constant(tolua_S, "CLOCK_WISE", 0);
        tolua_constant(tolua_S, "COUNTER_CLOCK_WISE", 1);
    tolua_endmodule(tolua_S);

    auto typeName = typeid(cocos2d::backend::Winding).name(); // rtti is literal storage
    g_luaType[reinterpret_cast<uintptr_t>(typeName)] = "ccb.Winding";
    g_typeCast[typeName] = "ccb.Winding";
    return 1;
}

int lua_register_cc_backend_TextureCubeFace(lua_State* tolua_S)
{
    tolua_module(tolua_S, "TextureCubeFace", 0);
    tolua_beginmodule(tolua_S,"TextureCubeFace");
        tolua_constant(tolua_S, "POSITIVE_X", 0);
        tolua_constant(tolua_S, "NEGATIVE_X", 1);
        tolua_constant(tolua_S, "POSITIVE_Y", 2);
        tolua_constant(tolua_S, "NEGATIVE_Y", 3);
        tolua_constant(tolua_S, "POSITIVE_Z", 4);
        tolua_constant(tolua_S, "NEGATIVE_Z", 5);
    tolua_endmodule(tolua_S);

    auto typeName = typeid(cocos2d::backend::TextureCubeFace).name(); // rtti is literal storage
    g_luaType[reinterpret_cast<uintptr_t>(typeName)] = "ccb.TextureCubeFace";
    g_typeCast[typeName] = "ccb.TextureCubeFace";
    return 1;
}
int lua_cc_backend_Program_getVertexLayout(lua_State* tolua_S);
int lua_cc_backend_Program_getUniformLocation(lua_State* tolua_S);
int lua_cc_backend_Program_getActiveAttributes(lua_State* tolua_S);
int lua_cc_backend_Program_getAttributeLocation(lua_State* tolua_S);
int lua_cc_backend_VertexLayout_constructor(lua_State* tolua_S);
int lua_cc_backend_VertexLayout_setAttribute(lua_State* tolua_S);
int lua_cc_backend_VertexLayout_setStride(lua_State* tolua_S);
int lua_cc_backend_ProgramState_constructor(lua_State* tolua_S);
int lua_cc_backend_ProgramState_setTexture(lua_State* tolua_S);
int lua_cc_backend_ProgramState_getAttributeLocation(lua_State* tolua_S);
int lua_cc_backend_ProgramState_setVertexLayout(lua_State* tolua_S);
int lua_cc_backend_ProgramState_setVertexAttrib(lua_State* tolua_S);
int lua_cc_backend_ProgramState_validateSharedVertexLayout(lua_State* tolua_S);
int lua_cc_backend_TextureBackend_updateSamplerDescriptor(lua_State* tolua_S);
int lua_cc_backend_TextureBackend_updateTextureDescriptor(lua_State* tolua_S);
int lua_cc_backend_Texture2DBackend_getHeight(lua_State* tolua_S);
int lua_cc_backend_Texture2DBackend_getWidth(lua_State* tolua_S);
int lua_cc_backend_Texture2DBackend_updateData(lua_State* tolua_S);
int lua_cc_backend_Texture2DBackend_updateCompressedData(lua_State* tolua_S);
int lua_cc_backend_Texture2DBackend_updateSubData(lua_State* tolua_S);
int lua_cc_backend_Texture2DBackend_updateCompressedSubData(lua_State* tolua_S);
int lua_cc_backend_TextureCubemapBackend_updateFaceData(lua_State* tolua_S);
int lua_cc_backend_Device_newDefaultRenderTarget(lua_State* tolua_S);
int lua_cc_backend_Device_newRenderTarget(lua_State* tolua_S);
int lua_cc_backend_Device_newDepthStencilState(lua_State* tolua_S);

int register_all_cc_backend_retained(lua_State* L)
{
    tolua_module(L,"ccb",0); tolua_beginmodule(L,"ccb");
    lua_register_cc_backend_BufferUsage(L);
    lua_register_cc_backend_BufferType(L);
    lua_register_cc_backend_ShaderStage(L);
    lua_register_cc_backend_VertexFormat(L);
    lua_register_cc_backend_PixelFormat(L);
    lua_register_cc_backend_TextureUsage(L);
    lua_register_cc_backend_IndexFormat(L);
    lua_register_cc_backend_VertexStepMode(L);
    lua_register_cc_backend_PrimitiveType(L);
    lua_register_cc_backend_TextureType(L);
    lua_register_cc_backend_SamplerAddressMode(L);
    lua_register_cc_backend_SamplerFilter(L);
    lua_register_cc_backend_StencilOperation(L);
    lua_register_cc_backend_CompareFunction(L);
    lua_register_cc_backend_BlendOperation(L);
    lua_register_cc_backend_BlendFactor(L);
    lua_register_cc_backend_ColorWriteMask(L);
    lua_register_cc_backend_CullMode(L);
    lua_register_cc_backend_Winding(L);
    lua_register_cc_backend_TextureCubeFace(L);
    tolua_endmodule(L);
    luaL_getmetatable(L,"ccb.Program");
    if (lua_istable(L,-1)) {
        tolua_function(L,"getVertexLayout",lua_cc_backend_Program_getVertexLayout);
        tolua_function(L,"getUniformLocation",lua_cc_backend_Program_getUniformLocation);
        tolua_function(L,"getActiveAttributes",lua_cc_backend_Program_getActiveAttributes);
        tolua_function(L,"getAttributeLocation",lua_cc_backend_Program_getAttributeLocation);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"ccb.VertexLayout");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_backend_VertexLayout_constructor);
        tolua_function(L,"setAttribute",lua_cc_backend_VertexLayout_setAttribute);
        tolua_function(L,"setStride",lua_cc_backend_VertexLayout_setStride);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"ccb.ProgramState");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_backend_ProgramState_constructor);
        tolua_function(L,"setTexture",lua_cc_backend_ProgramState_setTexture);
        tolua_function(L,"getAttributeLocation",lua_cc_backend_ProgramState_getAttributeLocation);
        tolua_function(L,"setVertexLayout",lua_cc_backend_ProgramState_setVertexLayout);
        tolua_function(L,"setVertexAttrib",lua_cc_backend_ProgramState_setVertexAttrib);
        tolua_function(L,"validateSharedVertexLayout",lua_cc_backend_ProgramState_validateSharedVertexLayout);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"ccb.TextureBackend");
    if (lua_istable(L,-1)) {
        tolua_function(L,"updateSamplerDescriptor",lua_cc_backend_TextureBackend_updateSamplerDescriptor);
        tolua_function(L,"updateTextureDescriptor",lua_cc_backend_TextureBackend_updateTextureDescriptor);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"ccb.Texture2DBackend");
    if (lua_istable(L,-1)) {
        tolua_function(L,"getHeight",lua_cc_backend_Texture2DBackend_getHeight);
        tolua_function(L,"getWidth",lua_cc_backend_Texture2DBackend_getWidth);
        tolua_function(L,"updateData",lua_cc_backend_Texture2DBackend_updateData);
        tolua_function(L,"updateCompressedData",lua_cc_backend_Texture2DBackend_updateCompressedData);
        tolua_function(L,"updateSubData",lua_cc_backend_Texture2DBackend_updateSubData);
        tolua_function(L,"updateCompressedSubData",lua_cc_backend_Texture2DBackend_updateCompressedSubData);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"ccb.TextureCubemapBackend");
    if (lua_istable(L,-1)) {
        tolua_function(L,"updateFaceData",lua_cc_backend_TextureCubemapBackend_updateFaceData);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"ccb.Device");
    if (lua_istable(L,-1)) {
        tolua_function(L,"newDefaultRenderTarget",lua_cc_backend_Device_newDefaultRenderTarget);
        tolua_function(L,"newRenderTarget",lua_cc_backend_Device_newRenderTarget);
        tolua_function(L,"newDepthStencilState",lua_cc_backend_Device_newDepthStencilState);
    }
    lua_pop(L,1);
    return 0;
}
