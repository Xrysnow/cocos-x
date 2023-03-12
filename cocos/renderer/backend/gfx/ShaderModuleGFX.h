#pragma once
#include "renderer/backend/ShaderModule.h"
#include "gfx/backend/GFXDeviceManager.h"
#include "glslang/Public/ShaderLang.h"

CC_BACKEND_BEGIN

class ShaderModuleGFX : public ShaderModule
{
public:
    ShaderModuleGFX(ShaderStage stage, std::string_view source);
    ShaderModuleGFX(const cc::gfx::ShaderStage& stage);
    ~ShaderModuleGFX() override;

    const cc::gfx::ShaderStage& getGFXShaderStage() const { return _gfxStage; }
    glslang::TShader* getGLSLangShader() const { return _glslangShader; }

private:
    void init();
    cc::gfx::ShaderStage _gfxStage;
    glslang::TShader* _glslangShader = nullptr;
    friend class ProgramGFX;
};

CC_BACKEND_END
