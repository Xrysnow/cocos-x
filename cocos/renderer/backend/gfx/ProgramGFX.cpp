#include "ProgramGFX.h"
#include "renderer/backend/Types.h"
#include "base/ccMacros.h"
#include "base/CCDirector.h"
#include "base/CCEventDispatcher.h"
#include "base/CCEventType.h"
#include "ShaderModuleGFX.h"
#include "UtilsGFX.h"
#include "glslang/glslang/Public/ShaderLang.h"
#include "glslang/SPIRV/GlslangToSpv.h"
#include "spirv_cross/spirv_msl.hpp"
#include "TextureGFX.h"
#include <regex>

using namespace cc;

CC_BACKEND_BEGIN

// The vertex language has the following predeclared globally scoped default precision statements:
//		precision highp float;
//		precision highp int;
//		precision lowp sampler2D;
//		precision lowp samplerCube;
// The fragment language has the following predeclared globally scoped default precision statements:
//		precision mediump int;
//		precision lowp sampler2D;
//		precision lowp samplerCube;
// The fragment language has no default precision qualifier for floating point types.

static std::unordered_map<gfx::ShaderStageFlagBit, std::string> StagesPredefine = {
    {gfx::ShaderStageFlagBit::VERTEX, "precision highp float;\nprecision highp int;\n"},
    {gfx::ShaderStageFlagBit::FRAGMENT, "precision mediump float;\nprecision mediump int;\n"},
};

cc::gfx::AttributeList ProgramGFX::builtinAttributes                  = {};
cc::gfx::UniformBlockList ProgramGFX::builtinUniforms                 = {};
cc::gfx::UniformSamplerTextureList ProgramGFX::builtinSamplerTextures = {};

cocos2d::Map<size_t, ShaderModuleGFX*> ProgramGFX::cachedModules;
std::unordered_map<size_t, ProgramGFX*> ProgramGFX::cachedPrograms;

ProgramGFX::ProgramGFX(const cc::gfx::ShaderInfo& shaderInfo) : Program("", "")
{
    UtilsGFX::glslangInitialize();
    hash = std::hash<cc::gfx::ShaderInfo>{}(shaderInfo);
    if (cachedPrograms.find(hash) != cachedPrograms.end())
    {
        const auto program = cachedPrograms.at(hash);
        _program           = program->_program;
        CC_SAFE_ADD_REF(_program);
        defaultDescriptorSetLayout = program->defaultDescriptorSetLayout;
        CC_SAFE_ADD_REF(defaultDescriptorSetLayout);
        defaultPipelineLayout = program->defaultPipelineLayout;
        CC_SAFE_ADD_REF(defaultPipelineLayout);
        _info                  = program->_info;
        modules                = program->modules;
        totalUniformSize       = program->totalUniformSize;
        uniformLayoutBindings  = program->uniformLayoutBindings;
        attributeInfos         = program->attributeInfos;
        activeUniformLocations = program->activeUniformLocations;
        activeUniformInfos     = program->activeUniformInfos;
        blockInfoEx            = program->blockInfoEx;
        samplers               = program->samplers;
        return;
    }
    if (cachedPrograms.empty())
        addPurageListener();
    cachedPrograms[hash] = this;
    retain();

    auto& stages = shaderInfo.stages;
    for (auto& stage : stages)
    {
        const auto it = StagesPredefine.find(stage.stage);
        if (it != StagesPredefine.end())
        {
            gfx::ShaderStage s;
            s.stage  = stage.stage;
            s.source = it->second + stage.source;
            modules.pushBack(getShaderModule(s));
        }
        else
        {
            modules.pushBack(getShaderModule(stage));
        }
    }

    auto glslangProgram = ccnew(glslang::TProgram)();
    for (auto& m : modules)
    {
        const auto shader = m->getGLSLangShader();
        if (!shader)
        {
            log("%s: invalid GLSL shader", __FUNCTION__);
            CC_SAFE_DELETE(glslangProgram);
            return;
        }
        glslangProgram->addShader(shader);
    }

    if (!glslangProgram->link((EShMessages)(EShMsgSpvRules | EShMsgVulkanRules)))
    {
        log("GLSL Linking Failed:\n%s\n%s", glslangProgram->getInfoLog(), glslangProgram->getInfoDebugLog());
        return;
    }

    if (!glslangProgram->buildReflection())
    {
        log("GLSL Reflection Failed");
        return;
    }
    // note: 'computeShaderInfo' can only get active resources
    computeShaderInfo(glslangProgram, _info, blockInfoEx);

    if (!shaderInfo.attributes.empty())
    {
        // check
        std::unordered_map<std::string, size_t> map;
        int i = 0;
        for (auto& a : _info.attributes)
        {
            map[a.name] = i;
            ++i;
        }
        for (auto& a : shaderInfo.attributes)
        {
            const auto it = map.find(a.name);
            if (it != map.end())
            {
                auto& target = _info.attributes.at(it->second);
                if (a.location != target.location)
                {
                    log("%s: attribute '%s' location mismatch, expect %d, got %d",
                        __FUNCTION__,
                        a.name.c_str(),
                        target.location,
                        a.location);
                }
            }
            else
            {
                // attribute is not active in shader
            }
        }
        _info.attributes = shaderInfo.attributes;
    }
    else
    {
        // attributes should not be empty
        log("%s: no attributes is given", __FUNCTION__);
    }

    if (!shaderInfo.blocks.empty())
    {
        // check
        std::unordered_map<std::string, size_t> map;
        int i = 0;
        for (auto& b : _info.blocks)
        {
            map[b.name] = i;
            ++i;
        }
        for (auto& b : shaderInfo.blocks)
        {
            const auto it = map.find(b.name);
            if (it != map.end())
            {
                auto& target = _info.blocks.at(it->second);
                // binding can be different?
                if (b.binding != target.binding || b.set != target.set)
                {
                    log("%s: uniform block '%s' mismatch, expect binding=%d set=%d, got binding=%d set=%d",
                        __FUNCTION__,
                        b.name.c_str(),
                        target.binding,
                        target.set,
                        b.binding,
                        b.set);
                }
                // compare sequence
                for (size_t j = 0; j < std::max(b.members.size(), target.members.size()); ++j)
                {
                    if (j >= b.members.size())
                    {
                        log("%s: uniform '%s' in block '%s' is not assigned",
                            __FUNCTION__,
                            target.members.at(j).name.c_str(),
                            b.name.c_str());
                    }
                    else if (j >= target.members.size())
                    {
                        log("%s: uniform '%s' in block '%s' is not in shader",
                            __FUNCTION__,
                            b.members.at(j).name.c_str(),
                            b.name.c_str());
                    }
                    else
                    {
                        const auto& u1 = b.members.at(j);
                        const auto& u2 = target.members.at(j);
                        if (u1.name != u2.name || u1.type != u2.type)
                        {
                            log("%s: uniform name mismatch, expect name='%s' type=%d, got name='%s' type=%d",
                                __FUNCTION__,
                                u2.name.c_str(),
                                (int)u2.type,
                                u1.name.c_str(),
                                (int)u1.type);
                        }
                    }
                }

                /*
                std::unordered_map<std::string, size_t> targetMemberMap;
                std::unordered_map<std::string, size_t> srcMemberMap;
                i = 0;
                for (auto& u : b.members)
                {
                        srcMemberMap[u.name] = i;
                        ++i;
                }
                i = 0;
                for (auto& u : target.members)
                {
                        targetMemberMap[u.name] = i;
                        ++i;
                        if (!srcMemberMap.count(u.name))
                        {
                                log("%s: uniform '%s' in block '%s' is not assigned",
                                        __FUNCTION__, u.name.c_str(), b.name.c_str());
                        }
                }
                for (auto& u : b.members)
                {
                        if (targetMemberMap.count(u.name))
                        {
                                // uniform is active
                                auto& target_u = target.members.at(targetMemberMap.at(u.name));
                                if (u.name != target_u.name || u.type != target_u.type)
                                {
                                        log("%s: uniform name mismatch, expect name='%s' type=%d, got name='%s'
                type=%d",
                                                __FUNCTION__, target_u.name.c_str(), (int)target_u.type, u.name.c_str(),
                (int)u.type);
                                }
                        }
                        else
                        {
                                // uniform is not active
                        }
                }
                */
            }
            else
            {
                // uniform block is not active
            }
        }
        _info.blocks = shaderInfo.blocks;
    }

    if (!shaderInfo.samplerTextures.empty())
    {
        // check
        std::unordered_map<std::string, size_t> tartgetMap;
        std::unordered_map<std::string, size_t> srcMap;
        int i = 0;
        for (auto& s : shaderInfo.samplerTextures)
        {
            srcMap[s.name] = i;
            ++i;
        }
        i = 0;
        for (auto& s : _info.samplerTextures)
        {
            tartgetMap[s.name] = i;
            ++i;
            if (!srcMap.count(s.name))
            {
                log("%s: sampler texture '%s' is not assigned", __FUNCTION__, s.name.c_str());
            }
        }
        for (auto& s : shaderInfo.samplerTextures)
        {
            const auto it = tartgetMap.find(s.name);
            if (it != tartgetMap.end())
            {
                auto& target = _info.samplerTextures.at(it->second);
                // binding can be different?
                if (s.binding != target.binding || s.set != target.set || s.type != target.type)
                {
                    log("%s: sampler texture '%s' mismatch, expect binding=%d set=%d type=%d, got binding=%d set=%d "
                        "type=%d",
                        __FUNCTION__,
                        s.name.c_str(),
                        target.binding,
                        target.set,
                        (int)target.type,
                        s.binding,
                        s.set,
                        (int)s.type);
                }
            }
            else
            {
                // uniform is not active
            }
        }
        _info.samplerTextures = shaderInfo.samplerTextures;
    }

    std::vector<cc::gfx::ShaderStageFlagBit> compileStages;
    for (auto& m : modules)
    {
        compileStages.push_back(m->getGFXShaderStage().stage);
    }
    const auto api = gfx::Device::getInstance()->getGfxAPI();
    if (api == gfx::API::GLES2 || api == gfx::API::WEBGL)
    {
        fixForGLES2(_info);
        SpirvCodes spirvCodes = compileSpirvCodes(glslangProgram, compileStages);
        for (auto& stage : stages)
        {
            gfx::ShaderStage s;
            s.stage  = stage.stage;
            s.source = UtilsGFX::compileSPIRVtoGLSL(spirvCodes[stage.stage], 100, true);
            _info.stages.emplace_back(s);
        }
    }
    else if (api == gfx::API::GLES3 || api == gfx::API::WEBGL2)
    {
        SpirvCodes spirvCodes = compileSpirvCodes(glslangProgram, compileStages);
        for (auto& stage : stages)
        {
            gfx::ShaderStage s;
            s.stage  = stage.stage;
            s.source = UtilsGFX::compileSPIRVtoGLSL(spirvCodes[stage.stage], 310, true);
            _info.stages.emplace_back(s);
        }
    }
    else
    {
        _info.stages = stages;
    }
    CC_SAFE_DELETE(glslangProgram);

    // copy others
    _info.name          = shaderInfo.name.empty() ? generateShaderName(shaderInfo, this) : shaderInfo.name;
    _info.buffers       = shaderInfo.buffers;
    _info.samplers      = shaderInfo.samplers;
    _info.textures      = shaderInfo.textures;
    _info.images        = shaderInfo.images;
    _info.subpassInputs = shaderInfo.subpassInputs;

    updateBlockInfoEx(_info, blockInfoEx);
    uniformLayoutBindings      = computeUniformLayoutBindings(_info);
    defaultDescriptorSetLayout = createDescriptorSetLayout({});
    CC_SAFE_ADD_REF(defaultDescriptorSetLayout);

    for (auto& attr : _info.attributes)
    {
        AttributeBindInfo info;
        info.attributeName                 = attr.name;
        info.location                      = attr.location;
        info.size                          = gfx::GFX_FORMAT_INFOS[(int)attr.format].size;
        attributeInfos[info.attributeName] = info;
    }
    for (auto& block : _info.blocks)
    {
        for (auto& u : block.members)
        {
            // NOTE: 0 means scalar, but the engine needs 1
            if (u.count == 0)
                u.count = 1;
        }
    }
    for (auto& info : blockInfoEx)
    {
        for (auto& it : info.second.members)
        {
            UniformLocation loc;
            loc.shaderStage                  = ShaderStage::VERTEX_AND_FRAGMENT;
            loc.location[0]                  = info.second.index;  // block index
            loc.location[1]                  = it.second.bufferOffset;
            activeUniformLocations[it.first] = loc;
            // 'activeUniformInfos' is flattened 'blockInfoEx'
            activeUniformInfos[it.first] = it.second;
        }
        totalUniformSize += info.second.size;
    }
    int stIndex = 0;
    for (auto& st : _info.samplerTextures)
    {
        UniformLocation loc;
        loc.shaderStage                 = ShaderStage::VERTEX_AND_FRAGMENT;
        loc.location[0]                 = stIndex;
        loc.location[1]                 = 0;
        activeUniformLocations[st.name] = loc;
        // only used for getting names by 'getAllActiveUniformInfo'
        activeUniformInfos[st.name] = {};
        ++stIndex;
    }

    _program = gfx::Device::getInstance()->createShader(_info);
    CC_ASSERT(_program);
    CC_SAFE_ADD_REF(_program);  // ref of cc::RefCounted is 0 when created

    //TODO: too much memory usage?
    //cachedModules.clear();
    //modules.clear();
}

ProgramGFX::~ProgramGFX()
{
    CC_SAFE_RELEASE_NULL(_program);
    CC_SAFE_RELEASE_NULL(defaultPipelineLayout);
    CC_SAFE_RELEASE_NULL(defaultDescriptorSetLayout);
}

void ProgramGFX::computeShaderInfo(
    glslang::TProgram* program, cc::gfx::ShaderInfo& info, std::unordered_map<std::string, BlockInfoEx>& blockInfoEx)
{
    info.attributes.clear();
    info.blocks.clear();
    info.samplerTextures.clear();
    for (int i = 0; i < program->getNumLiveAttributes(); ++i)
    {
        gfx::Attribute attr;
        attr.name       = program->getAttributeName(i);
        const auto& ref = program->getPipeInput(i);
        const auto& q   = ref.getType()->getQualifier();
        attr.location   = q.layoutLocation;
        attr.stream     = q.layoutStream == glslang::TQualifier::layoutStreamEnd ? 0u : q.layoutStream;
        attr.format     = UtilsGFX::toFormat(UtilsGFX::toType(ref.getType()));
        if (attr.format == gfx::Format::UNKNOWN)
        {
            log("%s: attribute '%s' has invalid format", __FUNCTION__, attr.name.c_str());
        }
        info.attributes.emplace_back(attr);
    }
    for (int i = 0; i < program->getNumLiveUniformBlocks(); ++i)
    {
        const auto& block = program->getUniformBlock(i);
        auto type         = block.getType();
        const auto& q     = type->getQualifier();
        gfx::UniformBlock ub;
        ub.name    = block.name;
        ub.binding = block.getBinding();
        ub.set     = q.layoutSet == glslang::TQualifier::layoutSetEnd ? 0u : q.layoutSet;
        // ub.count = 1; // seems not used

        BlockInfoEx ex;
        ex.name              = block.name;
        ex.size              = block.size;
        blockInfoEx[ex.name] = ex;

        CC_ASSERT(type->isStruct() && type->getStruct());
        // this should get all members in block
        const auto s = type->getStruct();
        for (auto& ty : (*s))
        {
            if (!ty.type->hiddenMember())
            {
                gfx::Uniform uniform;
                const auto& name = ty.type->getFieldName();
                uniform.name     = {name.c_str(), name.size()};
                uniform.type     = UtilsGFX::toType(ty.type);
                if (ty.type->isArray())
                {
                    uniform.count = ty.type->getOuterArraySize();
                }
                if (uniform.type == gfx::Type::UNKNOWN)
                {
                    log("%s: uniform '%s' has invalid type", __FUNCTION__, name.c_str());
                }
                ub.members.emplace_back(uniform);
                //
                UniformInfo uinfo;
                // 'size' means array size, =1 if not array
                uinfo.count = std::max(uniform.count, 1u);
                uinfo.type  = ty.type->getBasicType();
                uinfo.size  = gfx::getTypeSize(uniform.type);
                // NOTE: can not get offset here
                uinfo.bufferOffset                            = -1;
                uinfo.isArray                                 = ty.type->isArray();
                uinfo.isMatrix                                = ty.type->isMatrix();
                blockInfoEx[block.name].members[uniform.name] = uinfo;
            }
        }
        info.blocks.emplace_back(ub);
    }
    for (int i = 0; i < program->getNumLiveUniformVariables(); ++i)
    {
        const auto& u    = program->getUniform(i);
        const auto& name = u.name;
        const auto btype = u.getType()->getBasicType();
        if (btype != glslang::EbtSampler)
        {
            gfx::Uniform uniform;
            uniform.name = name;
            uniform.type = UtilsGFX::toType(u.getType());
            if (u.getType()->isArray())
            {
                uniform.count = u.getType()->getOuterArraySize();
                // uniform.count = u.size;
            }
            if (uniform.type == gfx::Type::UNKNOWN)
            {
                log("%s: uniform '%s' has invalid type", __FUNCTION__, name.c_str());
            }
            const auto block_idx = u.index;
            if (0 <= block_idx && block_idx < info.blocks.size())
            {
                auto& block = info.blocks.at(block_idx);
                if (!blockInfoEx[block.name].members.count(name))
                {
                    block.members.emplace_back(uniform);
                }
                UniformInfo uinfo;
                // 'size' means array size, =1 if not array
                uinfo.count = u.size;
                // uinfo.location = i;
                uinfo.type                            = u.glDefineType;
                uinfo.size                            = gfx::getTypeSize(uniform.type);
                uinfo.bufferOffset                    = u.offset;
                uinfo.isArray                         = u.getType()->isArray();
                uinfo.isMatrix                        = u.getType()->isMatrix();
                blockInfoEx[block.name].members[name] = uinfo;
            }
            else
            {
                log("%s: uniform '%s' is not in block", __FUNCTION__, name.c_str());
            }
        }
        else
        {
            // can be texture/image/subpass
            const auto& s = u.getType()->getSampler();
            const auto& q = u.getType()->getQualifier();
            gfx::UniformSamplerTexture ust;
            ust.name    = name;
            ust.binding = u.getBinding();
            ust.set     = q.layoutSet == glslang::TQualifier::layoutSetEnd ? 0u : q.layoutSet;
            ust.count   = 1;  // u.size?
            ust.type    = UtilsGFX::toType(u.getType());
            if (ust.type == gfx::Type::UNKNOWN)
            {
                log("%s: sampler uniform '%s' has invalid type '%s'",
                    __FUNCTION__,
                    name.c_str(),
                    s.getString().c_str());
            }
            if (!s.isCombined())
            {
                log("%s: sampler uniform '%s' is not combined", __FUNCTION__, name.c_str());
            }
            else
            {
                info.samplerTextures.emplace_back(ust);
            }
        }
    }
    /*
    for (auto& block : info.blocks)
    {
        auto& infoMap = blockInfoEx.at(block.name).members;
        std::sort(block.members.begin(), block.members.end(),
            [&](const gfx::Uniform& a, const gfx::Uniform& b)
            {
                return infoMap.at(a.name).bufferOffset < infoMap.at(b.name).bufferOffset;
            });
    }
    */
}

void ProgramGFX::updateBlockInfoEx(
    const cc::gfx::ShaderInfo& info, std::unordered_map<std::string, BlockInfoEx>& blockInfoEx)
{
    int i             = 0;
    const auto api    = gfx::Device::getInstance()->getGfxAPI();
    const auto legacy = api == gfx::API::GLES2 || api == gfx::API::WEBGL;
    for (auto& block : info.blocks)
    {
        if (blockInfoEx.find(block.name) == blockInfoEx.end())
        {
            // block not in program
            BlockInfoEx ex;
            ex.name  = block.name;
            ex.index = i;
            for (auto& u : block.members)
            {
                ex.size = UtilsGFX::getUniformStd140Offset(u.type, u.count, ex.size);
                UniformInfo uinfo;
                uinfo.count        = u.count;
                uinfo.size         = gfx::getTypeSize(u.type);
                uinfo.bufferOffset = ex.size;
                if (legacy)
                    ex.size += uinfo.size * std::max(u.count, 1u);
                else
                    ex.size += UtilsGFX::getUniformStd140Size(u.type, u.count);
                ex.members[u.name] = uinfo;
            }
            blockInfoEx[block.name] = ex;
        }
        else
        {
            // block is in program
            auto& ex         = blockInfoEx[block.name];
            ex.index         = i;
            uint32_t ex_size = 0;
            for (auto& u : block.members)
            {
                if (ex.members.find(u.name) == ex.members.end())
                {
                    ex_size = UtilsGFX::getUniformStd140Offset(u.type, u.count, ex_size);
                    // uniform not in program
                    UniformInfo uinfo;
                    uinfo.count        = u.count;
                    uinfo.size         = gfx::getTypeSize(u.type);
                    uinfo.bufferOffset = ex_size;
                    if (legacy)
                        ex_size += uinfo.size * std::max(u.count, 1u);
                    else
                        ex_size += UtilsGFX::getUniformStd140Size(u.type, u.count);
                    ex.members[u.name] = uinfo;
                }
                else
                {
                    ex_size = UtilsGFX::getUniformStd140Offset(u.type, u.count, ex_size);
                    // uniform is in program
                    auto& uinfo         = ex.members[u.name];
                    const auto size     = gfx::getTypeSize(u.type);
                    const auto gotCount = std::max(u.count, 1u);
                    // -1 means unknown
                    const bool offsetNotOk = !legacy && uinfo.bufferOffset != ex_size && uinfo.bufferOffset != -1;
                    if (uinfo.count != gotCount || uinfo.size != size || offsetNotOk)
                    {
                        log("%s '%s': uniform '%s' in block '%s' mismatch, expect count=%d size=%d offset=%d, got "
                            "count=%d size=%d offset=%d",
                            __FUNCTION__,
                            info.name.c_str(),
                            u.name.c_str(),
                            block.name.c_str(),
                            uinfo.count,
                            uinfo.size,
                            uinfo.bufferOffset,
                            gotCount,
                            size,
                            ex_size);
                    }
                    uinfo.count        = u.count;
                    uinfo.size         = size;
                    uinfo.bufferOffset = ex_size;
                    if (legacy)
                        ex_size += uinfo.size * std::max(u.count, 1u);
                    else
                        ex_size += UtilsGFX::getUniformStd140Size(u.type, u.count);
                }
            }
            if (!legacy && ex_size != ex.size)
            {
                log("%s '%s': uniform block '%s' mismatch, expect size=%d, got size=%d",
                    __FUNCTION__,
                    info.name.c_str(),
                    block.name.c_str(),
                    ex.size,
                    ex_size);
            }
            ex.size = ex_size;
        }
        ++i;
    }
}

void ProgramGFX::fixForGLES2(cc::gfx::ShaderInfo& info)
{
    // blocks have been converted to structures named '_BlockName', members should be accessed by '_BlockName.name'
    for (auto& block : info.blocks)
    {
        auto& name = block.name;
        for (auto& u : block.members)
        {
            u.name = "_" + name + "." + u.name;
        }
    }
}

cc::gfx::DescriptorSetLayoutBindingList ProgramGFX::computeUniformLayoutBindings(
    const cc::gfx::ShaderInfo& info, uint32_t set)
{
    gfx::DescriptorSetLayoutBindingList ret;

    std::unordered_set<uint32_t> usedBindings;
    std::map<uint32_t, uint32_t> buffersByBinding;
    const auto& blocks = info.blocks;
    const auto& sts    = info.samplerTextures;

    for (auto& block : blocks)
    {
        if (block.set == set)
        {
            const auto& binding = block.binding;
            if (buffersByBinding.find(binding) == buffersByBinding.end())
                buffersByBinding[binding] = 0;
            // UniformBlock.count is never used, should always be 1
            buffersByBinding[binding] += 1;
        }
    }

    for (auto& it : buffersByBinding)
    {
        gfx::DescriptorSetLayoutBinding lb;
        lb.binding = it.first;
        // lb.descriptorType = gfx::DescriptorType::DYNAMIC_UNIFORM_BUFFER;
        lb.descriptorType = gfx::DescriptorType::UNIFORM_BUFFER;
        lb.count          = it.second;  // should be 1
        lb.stageFlags     = gfx::ShaderStageFlagBit::VERTEX | gfx::ShaderStageFlagBit::FRAGMENT;
        ret.emplace_back(lb);
        usedBindings.insert(it.first);
    }

    for (auto& st : sts)
    {
        if (st.set != set)
            continue;
        if (usedBindings.count(st.binding))
        {
            log("%s: binding of sampler '%s' (%d) is already used", __FUNCTION__, st.name.c_str(), st.binding);
        }
        else
        {
            gfx::DescriptorSetLayoutBinding lb;
            lb.binding        = st.binding;
            lb.descriptorType = gfx::DescriptorType::SAMPLER_TEXTURE;
            lb.count          = st.count;
            lb.stageFlags     = gfx::ShaderStageFlagBit::VERTEX | gfx::ShaderStageFlagBit::FRAGMENT;
            ret.emplace_back(lb);
            usedBindings.insert(st.binding);
        }
    }

    return ret;
}

cc::gfx::DescriptorSetLayoutBindingList ProgramGFX::getUniformLayoutBindings(uint32_t set) const
{
    if (set == 0)
        return uniformLayoutBindings;
    return computeUniformLayoutBindings(_info, set);
}

cc::gfx::DescriptorSetLayout* ProgramGFX::createDescriptorSetLayout(
    const cc::gfx::DescriptorSetLayoutBindingList& extraBindings, uint32_t set)
{
    gfx::DescriptorSetLayoutInfo dslinfo;
    if (set == 0)
        dslinfo.bindings = uniformLayoutBindings;
    else
        dslinfo.bindings = computeUniformLayoutBindings(_info, set);
    for (auto& b : extraBindings)
        dslinfo.bindings.emplace_back(b);
    auto dsLayout = gfx::Device::getInstance()->createDescriptorSetLayout(dslinfo);
    CC_ASSERT(dsLayout);
    return dsLayout;
}

cc::gfx::PipelineLayout* ProgramGFX::getDefaultPipelineLayout()
{
    if (defaultPipelineLayout)
        return defaultPipelineLayout;
    gfx::PipelineLayoutInfo info;
    info.setLayouts       = {getDefaultDescriptorSetLayout()};
    defaultPipelineLayout = gfx::Device::getInstance()->createPipelineLayout(info);
    CC_SAFE_ADD_REF(defaultPipelineLayout);
    return defaultPipelineLayout;
}

void ProgramGFX::initDefaultInfo()
{
    if (builtinAttributes.empty())
    {
        // format should be streamed data format, not format in shader
        gfx::Attribute attr;
        attr.name     = ATTRIBUTE_NAME_POSITION;
        attr.location = (int)Attribute::POSITION;
        attr.format   = UtilsGFX::toAttributeType(VertexFormat::FLOAT3);
        builtinAttributes.emplace_back(attr);

        attr.name         = ATTRIBUTE_NAME_COLOR;
        attr.location     = (int)Attribute::COLOR;
        attr.format       = UtilsGFX::toAttributeType(VertexFormat::UBYTE4);
        attr.isNormalized = true;
        builtinAttributes.emplace_back(attr);
        attr.isNormalized = false;

        attr.name     = ATTRIBUTE_NAME_TEXCOORD;
        attr.location = (int)Attribute::TEXCOORD;
        attr.format   = UtilsGFX::toAttributeType(VertexFormat::FLOAT2);
        builtinAttributes.emplace_back(attr);

        attr.name     = ATTRIBUTE_NAME_TEXCOORD1;
        attr.location = (int)Attribute::TEXCOORD1;
        attr.format   = UtilsGFX::toAttributeType(VertexFormat::FLOAT2);
        builtinAttributes.emplace_back(attr);

        attr.name     = ATTRIBUTE_NAME_TEXCOORD2;
        attr.location = (int)Attribute::TEXCOORD2;
        attr.format   = UtilsGFX::toAttributeType(VertexFormat::FLOAT2);
        builtinAttributes.emplace_back(attr);

        attr.name     = ATTRIBUTE_NAME_TEXCOORD3;
        attr.location = (int)Attribute::TEXCOORD3;
        attr.format   = UtilsGFX::toAttributeType(VertexFormat::FLOAT2);
        builtinAttributes.emplace_back(attr);
    }
    if (builtinUniforms.empty())
    {
        gfx::UniformBlock block;
        block.name = "BuiltinUniformBlock";

        gfx::Uniform uniform;
        uniform.name = UNIFORM_NAME_MVP_MATRIX;
        uniform.type = gfx::Type::MAT4;
        block.members.emplace_back(uniform);

        uniform.name = UNIFORM_NAME_TEXT_COLOR;
        uniform.type = gfx::Type::FLOAT4;
        block.members.emplace_back(uniform);

        uniform.name = UNIFORM_NAME_EFFECT_COLOR;
        uniform.type = gfx::Type::FLOAT4;
        block.members.emplace_back(uniform);

        uniform.name = UNIFORM_NAME_EFFECT_TYPE;
        uniform.type = gfx::Type::INT;
        block.members.emplace_back(uniform);

        builtinUniforms.emplace_back(block);
    }
    if (builtinSamplerTextures.empty())
    {
        gfx::UniformSamplerTexture st;
        st.name = UNIFORM_NAME_TEXTURE;
        st.type = gfx::Type::SAMPLER2D;
        builtinSamplerTextures.emplace_back(st);

        st.name = UNIFORM_NAME_TEXTURE1;
        st.type = gfx::Type::SAMPLER2D;
        builtinSamplerTextures.emplace_back(st);

        st.name = UNIFORM_NAME_TEXTURE2;
        st.type = gfx::Type::SAMPLER2D;
        builtinSamplerTextures.emplace_back(st);

        st.name = UNIFORM_NAME_TEXTURE3;
        st.type = gfx::Type::SAMPLER2D;
        builtinSamplerTextures.emplace_back(st);
    }
}

ShaderModuleGFX* ProgramGFX::getShaderModule(const cc::gfx::ShaderStage& stage)
{
    const auto hash = std::hash<std::string>{}(stage.source);
    const auto it2  = cachedModules.find(hash);
    if (it2 != cachedModules.end())
    {
        return it2->second;
    }
    else
    {
        auto m = new ShaderModuleGFX(stage);
        m->autorelease();
        cachedModules.insert(hash, m);
        return m;
    }
}

ProgramGFX::SpirvCodes ProgramGFX::compileSpirvCodes(
    glslang::TProgram* tProgram, const std::vector<cc::gfx::ShaderStageFlagBit>& stages)
{
    SpirvCodes ret;
    for (auto&& stage : stages)
    {
        spv::SpvBuildLogger logger;
        glslang::SpvOptions spvOptions;
        std::vector<uint32_t> spirv;
        const auto envStage = UtilsGFX::toGLSLangShaderStage(stage);
        glslang::GlslangToSpv(*tProgram->getIntermediate(envStage), spirv, &logger, &spvOptions);
        if (spirv.empty())
        {
            log("GlslangToSpv Failed:\n%s\n%s", tProgram->getInfoLog(), tProgram->getInfoDebugLog());
            ret = {};
            break;
        }
        ret[stage] = spirv;
    }
    return ret;
}

std::string ProgramGFX::generateShaderName(const cc::gfx::ShaderInfo& shaderInfo, void* p)
{
    std::string shaderName = StringUtils::format("0x%x(", (uint32_t)p);
    for (auto& stage : shaderInfo.stages)
    {
        shaderName += StringUtils::format("%d+", (uint32_t)stage.source.size());
        auto hash = std::hash<std::string>{}(stage.source);
    }
    if (shaderName.back() == '+')
        shaderName.back() = ')';
    else
        shaderName.pop_back();
    return shaderName;
}

void ProgramGFX::addPurageListener()
{
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(Director::EVENT_RESET, [&](EventCustom*) {
        for (auto&& it : cachedPrograms)
        {
            CC_SAFE_RELEASE(it.second);
        }
        cachedPrograms.clear();
    });
}

const std::unordered_map<std::string, AttributeBindInfo>& ProgramGFX::getActiveAttributes() const
{
    return attributeInfos;
}

int ProgramGFX::getAttributeLocation(Attribute name) const
{
    static std::array<std::string, Attribute::ATTRIBUTE_MAX> AttributeMap = {
        ATTRIBUTE_NAME_POSITION,
        ATTRIBUTE_NAME_COLOR,
        ATTRIBUTE_NAME_TEXCOORD,
        ATTRIBUTE_NAME_TEXCOORD1,
        ATTRIBUTE_NAME_TEXCOORD2,
        ATTRIBUTE_NAME_TEXCOORD3};
    if (name >= Attribute::ATTRIBUTE_MAX)
        return -1;
    return getAttributeLocation(AttributeMap.at((int)name));
}

int ProgramGFX::getAttributeLocation(std::string_view name) const
{
    // -1 will make VertexLayout::setAttribute do nothing
    int i = 0;
    for (const auto& a : _info.attributes)
    {
        if (a.name == name)
            return i;
        ++i;
    }
    return -1;
}

UniformLocation ProgramGFX::getUniformLocation(backend::Uniform name) const
{
    static std::array<std::string, Uniform::UNIFORM_MAX> UniformMap = {
        UNIFORM_NAME_MVP_MATRIX,
        UNIFORM_NAME_TEXTURE,
        UNIFORM_NAME_TEXTURE1,
        UNIFORM_NAME_TEXTURE2,
        UNIFORM_NAME_TEXTURE3,
        UNIFORM_NAME_TEXT_COLOR,
        UNIFORM_NAME_EFFECT_TYPE,
        UNIFORM_NAME_EFFECT_COLOR};
    if (name >= Uniform::UNIFORM_MAX)
        return {};
    return getUniformLocation(UniformMap.at((int)name));
}

UniformLocation ProgramGFX::getUniformLocation(std::string_view uniform) const
{
    const auto it = activeUniformLocations.find(uniform);
    if (it != activeUniformLocations.end())
        return it->second;
#if defined(CC_DEBUG) && (CC_DEBUG > 0)
    if (uniform.substr(0, 2) != "u_")
        log("%s: no uniform %s", __FUNCTION__, uniform.data());
#endif
    return {};
}

int ProgramGFX::getMaxVertexLocation() const
{
    // unused
    return 0;
}

int ProgramGFX::getMaxFragmentLocation() const
{
    // unused
    return 0;
}

const UniformInfo& ProgramGFX::getActiveUniformInfo(ShaderStage stage, int location) const
{
    // unused
    static const UniformInfo s_emptyInfo{};
    return s_emptyInfo;
}

const std::unordered_map<std::string, UniformInfo>& ProgramGFX::getAllActiveUniformInfo(ShaderStage stage) const
{
    return activeUniformInfos;
}

std::size_t ProgramGFX::getUniformBufferSize(ShaderStage stage) const
{
    if (!_program)
        return 0;
    if (totalUniformSize == 0)
        return 128;
    return totalUniformSize;
}

std::size_t ProgramGFX::getUniformBlockSize(const std::string& blockName) const
{
    const auto it = blockInfoEx.find(blockName);
    if (it != blockInfoEx.end())
        return it->second.size;
    return 0;
}

//

ProgramStateGFX::ProgramStateGFX(ProgramGFX* program_, const cocos2d::Map<std::string, BufferGFX*>& buffers_)
{
    CC_ASSERT(program_);
    program = program_;
    CC_SAFE_RETAIN(program);
    if (!program->getHandler())
        return;
    const auto& infoEx = program->getBlockInfoEx();
    uint32_t allOffset = 0;
    for (auto& block : program->getShaderInfo().blocks)
    {
        const auto& name = block.name;
        auto buffer      = buffers_.at(name);
        if (buffer)
        {
            buffers.insert(name, buffer);  // owned by others
        }
        else
        {
            gfx::BufferInfo info;
            info.usage    = gfx::BufferUsageBit::UNIFORM;
            info.size     = program->getUniformBlockSize(name);
            info.memUsage = gfx::MemoryUsageBit::HOST;
            buffer        = new BufferGFX(info);  // owned by this
            buffer->autorelease();
            buffers.insert(name, buffer);
        }
        // offsets
        allBufferOffsets.emplace_back(allOffset);
        allOffset += infoEx.at(name).size;
        //
        if (!blocksByBinding.count(block.binding))
            blocksByBinding[block.binding] = {};
        blocksByBinding[block.binding].emplace_back(name);
    }
    for (auto& block : program->getShaderInfo().buffers)
    {
        const auto& name = block.name;
        auto buffer      = buffers_.at(name);
        if (buffer)
        {
            buffers.insert(name, buffer);  // owned by others
        }
        else
        {
            // should be set by 'setBuffer'
        }
        //
        if (!sbuffersByBinding.count(block.binding))
            sbuffersByBinding[block.binding] = {};
        sbuffersByBinding[block.binding].emplace_back(name);
    }

    gfx::DescriptorSetInfo info;
    info.layout   = program->getDefaultDescriptorSetLayout();
    descriptorSet = gfx::Device::getInstance()->createDescriptorSet(info);
    CC_SAFE_ADD_REF(descriptorSet);
}

ProgramStateGFX::~ProgramStateGFX()
{
    CC_SAFE_RELEASE_NULL(program);
    CC_SAFE_RELEASE_NULL(descriptorSet);
}

bool ProgramStateGFX::setBuffer(const std::string& blockName, BufferGFX* buffer)
{
    if (buffers.find(blockName) == buffers.end() || !buffer)
        return false;
    buffers.insert(blockName, buffer);
    return true;
}

BufferGFX* ProgramStateGFX::getBuffer(const std::string& blockName)
{
    return buffers.at(blockName);
}

bool ProgramStateGFX::setUniform(const std::string& name, const void* data, std::size_t size)
{
    return setUniform(program->getUniformLocation(name), data, size);
}

bool ProgramStateGFX::setUniform(const UniformLocation& loc, const void* data, std::size_t size)
{
    if (!program->getHandler())
        return false;
    const auto blockIndex = loc.location[0];
    const auto offset     = loc.location[1];
    const auto& blocks    = program->getShaderInfo().blocks;
    if (blockIndex < 0 || offset < 0 || blockIndex >= blocks.size())
        return false;
    const auto& blockName = blocks.at(blockIndex).name;
    const auto buffer     = buffers.at(blockName);
    if (!buffer)
        return false;
    buffer->update(data, size, offset);
    return true;
}

bool ProgramStateGFX::setAllBuffer(const void* data, std::size_t size)
{
    if (!program->getHandler())
        return false;
    if (!data || program->getUniformBufferSize(ShaderStage::VERTEX_AND_FRAGMENT) != size)
        return false;
    const auto& blocks = program->getShaderInfo().blocks;
    const auto& infoEx = program->getBlockInfoEx();
    auto data_head     = (const char*)data;
    for (auto& b : blocks)
    {
        auto buffer           = buffers.at(b.name);
        const auto block_size = infoEx.at(b.name).size;
        if (buffer)
        {
            buffer->update(data_head, block_size);
        }
        data_head += block_size;
    }
    return true;
}

int32_t ProgramStateGFX::getAllBufferOffset(const UniformLocation& loc)
{
    if (!program->getHandler())
        return -1;
    const auto blockIndex = loc.location[0];
    const auto offset     = loc.location[1];
    if (blockIndex < 0 || blockIndex >= allBufferOffsets.size() || offset < 0)
    {
        return -1;
    }
    return allBufferOffsets.at(blockIndex) + offset;
}

bool ProgramStateGFX::syncTextures(ProgramStateGFX* dst)
{
    if (!dst || dst->program != program)
        return false;
    dst->textures = textures;
    return true;
}

bool ProgramStateGFX::setTexture(const std::string& name, TextureBackend* texture, uint32_t index)
{
    if (!textures.count(name))
        textures[name] = {};
    textures[name].insert(index, texture);
    return true;
}

bool ProgramStateGFX::setTexture(const UniformLocation& loc, TextureBackend* texture, uint32_t index)
{
    const auto& sts = program->getShaderInfo().samplerTextures;
    const auto idx  = loc.location[0];
    if (idx < 0 || idx >= sts.size() || index >= sts.at(idx).count || !texture)
    {
        return false;
    }
    const auto& st = sts.at(idx);
    return setTexture(st.name, texture, index);
}

void ProgramStateGFX::bindBuffers(cc::gfx::DescriptorSet* ds, uint32_t set)
{
    if (!program->getHandler())
        return;
    const auto& blocks   = program->getShaderInfo().blocks;
    const auto& sbuffers = program->getShaderInfo().buffers;
    const auto& infoEx   = program->getBlockInfoEx();
    for (auto& it : blocksByBinding)
    {
        int idx = 0;
        for (auto& name : it.second)
        {
            const auto buffer = buffers.at(name);
            const auto& block = blocks.at(infoEx.at(name).index);
            if (buffer && block.set == set)
            {
                ds->bindBuffer(it.first, buffer->getHandler(), idx);
                ++idx;
            }
        }
    }
    for (auto& it : sbuffersByBinding)
    {
        int idx = 0;
        for (auto& name : it.second)
        {
            const auto buffer = buffers.at(name);
            const auto& block = sbuffers.at(infoEx.at(name).index);
            if (buffer && block.set == set)
            {
                ds->bindBuffer(it.first, buffer->getHandler(), idx);
                ++idx;
            }
        }
    }
}

void ProgramStateGFX::bindTextures(cc::gfx::DescriptorSet* ds, uint32_t set)
{
    if (!program->getHandler())
        return;
    const auto& sts = program->getShaderInfo().samplerTextures;
    for (auto& st : sts)
    {
        if (st.set != set)
            continue;
        if (textures.find(st.name) == textures.end())
        {
            CCASSERT(false, "texture uniform not set");
            continue;
        }
        for (auto& it : textures.at(st.name))
        {
            const auto index = it.first;
            const auto tex   = it.second;
            if (tex && index < st.count)
            {
                // log("%s: bind texture 0x%x to uniform %s, slot=%d, size=(%d, %d)",
                //	__FUNCTION__, (intptr_t)getHandler(tex), st.name.c_str(), index,
                //	getHandler(tex)->getWidth(), getHandler(tex)->getHeight());
                ds->bindTexture(st.binding, UtilsGFX::getTexture(tex), index);
                ds->bindSampler(st.binding, UtilsGFX::getSampler(tex), index);
            }
        }
    }
}

void ProgramStateGFX::bindBuffers(uint32_t set)
{
    bindBuffers(descriptorSet, set);
}

void ProgramStateGFX::bindTextures(uint32_t set)
{
    bindTextures(descriptorSet, set);
}

CC_BACKEND_END
