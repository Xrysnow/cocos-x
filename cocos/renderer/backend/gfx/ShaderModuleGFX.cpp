#include "ShaderModuleGFX.h"
#include "platform/CCPlatformMacros.h"
#include "base/ccMacros.h"
#include "UtilsGFX.h"

using namespace cc;

CC_BACKEND_BEGIN

ShaderModuleGFX::ShaderModuleGFX(ShaderStage stage, std::string_view source) : ShaderModule(stage)
{
    switch (stage)
    {
    case ShaderStage::VERTEX:
        _gfxStage.stage = gfx::ShaderStageFlagBit::VERTEX;
        break;
    case ShaderStage::FRAGMENT:
        _gfxStage.stage = gfx::ShaderStageFlagBit::FRAGMENT;
        break;
    // case ShaderStage::VERTEX_AND_FRAGMENT:
    //	_gfxStage.stage = gfx::ShaderStageFlagBit::VERTEX | gfx::ShaderStageFlagBit::FRAGMENT;
    //	break;
    default:;
    }
    if (source.empty())
    {
        return;
    }
    if (source.at(0) != '#')
    {
        _gfxStage.source = "#version 320 es\n" + std::string{source};
    }
    else
    {
        _gfxStage.source = source;
    }
    init();
}

ShaderModuleGFX::ShaderModuleGFX(const cc::gfx::ShaderStage& stage) : ShaderModule(ShaderStage::VERTEX_AND_FRAGMENT)
{
    _gfxStage = stage;
    if (_gfxStage.source.at(0) != '#')
    {
        _gfxStage.source = "#version 320 es\n" + _gfxStage.source;
    }
    init();
}

ShaderModuleGFX::~ShaderModuleGFX()
{
    CC_SAFE_DELETE(_glslangShader);
}

void ShaderModuleGFX::init()
{
    int vkMinorVersion                    = 2;
    const int clientInputSemanticsVersion = 100 + vkMinorVersion * 10;
    const bool isForwardCompatible        = false;
    const EShMessages controls            = (EShMessages)(EShMsgSpvRules | EShMsgVulkanRules);
    const auto envStage                   = UtilsGFX::toGLSLangShaderStage(_gfxStage.stage);
    _glslangShader                        = ccnew(glslang::TShader)(envStage);
    const char* vstring                   = _gfxStage.source.c_str();
    const int vlength                     = _gfxStage.source.size();
    _glslangShader->setStringsWithLengths(&vstring, &vlength, 1);
    // -> #define VULKAN 1X0
    _glslangShader->setEnvInput(
        glslang::EShSourceGlsl, envStage, glslang::EShClientVulkan, clientInputSemanticsVersion);
    //-> Vulkan 1.X
    _glslangShader->setEnvClient(glslang::EShClientVulkan, UtilsGFX::toGLSLangClientVersion(vkMinorVersion));
    // -> SPIR-V 1.Y
    _glslangShader->setEnvTarget(glslang::EshTargetSpv, UtilsGFX::toGLSLangTargetVersion(vkMinorVersion));
    const bool success = _glslangShader->parse(
        &UtilsGFX::DefaultTBuiltInResource, clientInputSemanticsVersion, isForwardCompatible, controls);
    if (!success)
    {
        log("%s: GLSLang Parsing Failed:\n%s\n%s",
            __FUNCTION__,
            _glslangShader->getInfoLog(),
            _glslangShader->getInfoDebugLog());
        log("%s: source:\n%s", __FUNCTION__, _gfxStage.source.c_str());
        CC_SAFE_DELETE(_glslangShader);
    }
    setHashValue(std::hash<std::string>{}(_gfxStage.source));
}

CC_BACKEND_END
