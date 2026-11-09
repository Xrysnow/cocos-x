#include "scripting/lua-bindings/manual/lua_conversion/lua_conversion.hpp"
#include "renderer/backend/Device.h"
#include "renderer/backend/ProgramState.h"

// Only ownership and byte-buffer adaptation live here. Ordinary calls are generated.
static int backend_Program_getVertexLayout(lua_State* lua_S)
{
    LUA_INVOKE_HEADER("ccb.Program", "ccb.Program:getVertexLayout");
    const auto snapshot = [](const cocos2d::backend::Program* self) {
        const auto layout = self->getVertexLayout();
        return lua::owned_value<cocos2d::backend::VertexLayout>{
            layout ? new cocos2d::backend::VertexLayout(*layout) : nullptr};
    };
    LUA_TRY_INVOKE_R(0, snapshot);
    LUA_INVOKE_FOOTER("0");
}

static int backend_ProgramState_clone(lua_State* lua_S)
{
    LUA_INVOKE_HEADER("ccb.ProgramState", "ccb.ProgramState:clone");
    const auto clone = [](const cocos2d::backend::ProgramState* self) {
        auto result = self->clone();
        if (result) result->autorelease(); // Consume exactly the returned initial +1.
        return result;
    };
    LUA_TRY_INVOKE_R(0, clone);
    LUA_INVOKE_FOOTER("0");
}

static int backend_Device_newProgram(lua_State* lua_S)
{
    LUA_INVOKE_HEADER("ccb.Device", "ccb.Device:newProgram");
    const auto create = [](cocos2d::backend::Device* self, std::string_view vertex, std::string_view fragment) {
        auto result = self->newProgram(vertex, fragment);
        if (result) result->autorelease(); // Cached and other borrowed programs never pass here.
        return result;
    };
    LUA_TRY_INVOKE_R(2, create);
    LUA_INVOKE_FOOTER("2");
}

static int backend_ProgramState_setUniform(lua_State* lua_S)
{
    LUA_INVOKE_HEADER("ccb.ProgramState", "ccb.ProgramState:setUniform");
    const auto location = [](cocos2d::backend::ProgramState* self,
                             const cocos2d::backend::UniformLocation& where, const std::vector<uint8_t>& bytes) {
        self->setUniform(where, bytes.data(), bytes.size());
    };
    const auto name = [](cocos2d::backend::ProgramState* self,
                         std::string_view where, const std::vector<uint8_t>& bytes) {
        self->setUniform(self->getUniformLocation(where), bytes.data(), bytes.size());
    };
    LUA_TRY_INVOKE_OVERLOAD(2, location);
    LUA_TRY_INVOKE_OVERLOAD(2, name);
    LUA_INVOKE_FOOTER("2");
}

template<typename T>
static void backend_enum_identity(const char* name)
{
    const auto native = typeid(T).name();
    g_luaType[reinterpret_cast<uintptr_t>(native)] = name;
    g_typeCast[native] = name;
}

int register_all_cc_backend_manual(lua_State* L)
{
    // Enumeration values are generated; preserve the pre-existing RTTI identities.
    backend_enum_identity<cocos2d::backend::BufferUsage>("ccb.BufferUsage");
    backend_enum_identity<cocos2d::backend::BufferType>("ccb.BufferType");
    backend_enum_identity<cocos2d::backend::ShaderStage>("ccb.ShaderStage");
    backend_enum_identity<cocos2d::backend::VertexFormat>("ccb.VertexFormat");
    backend_enum_identity<cocos2d::backend::PixelFormat>("ccb.PixelFormat");
    backend_enum_identity<cocos2d::backend::TextureUsage>("ccb.TextureUsage");
    backend_enum_identity<cocos2d::backend::IndexFormat>("ccb.IndexFormat");
    backend_enum_identity<cocos2d::backend::VertexStepMode>("ccb.VertexStepMode");
    backend_enum_identity<cocos2d::backend::PrimitiveType>("ccb.PrimitiveType");
    backend_enum_identity<cocos2d::backend::TextureType>("ccb.TextureType");
    backend_enum_identity<cocos2d::backend::SamplerAddressMode>("ccb.SamplerAddressMode");
    backend_enum_identity<cocos2d::backend::SamplerFilter>("ccb.SamplerFilter");
    backend_enum_identity<cocos2d::backend::StencilOperation>("ccb.StencilOperation");
    backend_enum_identity<cocos2d::backend::CompareFunction>("ccb.CompareFunction");
    backend_enum_identity<cocos2d::backend::BlendOperation>("ccb.BlendOperation");
    backend_enum_identity<cocos2d::backend::BlendFactor>("ccb.BlendFactor");
    backend_enum_identity<cocos2d::backend::ColorWriteMask>("ccb.ColorWriteMask");
    backend_enum_identity<cocos2d::backend::CullMode>("ccb.CullMode");
    backend_enum_identity<cocos2d::backend::Winding>("ccb.Winding");
    backend_enum_identity<cocos2d::backend::TextureCubeFace>("ccb.TextureCubeFace");
    const auto method = [L](const char* type, const char* name, lua_CFunction function) {
        luaL_getmetatable(L, type);
        tolua_function(L, name, function);
        lua_pop(L, 1);
    };
    method("ccb.Program", "getVertexLayout", backend_Program_getVertexLayout);
    method("ccb.ProgramState", "clone", backend_ProgramState_clone);
    method("ccb.ProgramState", "setUniform", backend_ProgramState_setUniform);
    method("ccb.Device", "newProgram", backend_Device_newProgram);
    return 0;
}
