#pragma once
#include "renderer/backend/Macros.h"
#include "renderer/backend/Types.h"
#include "base/CCRef.h"
#include "base/CCEventListenerCustom.h"
#include "base/CCMap.h"
#include "base/CCVector.h"
#include "renderer/backend/Program.h"
#include "gfx/backend/GFXDeviceManager.h"
#include "glslang/glslang/Public/ShaderLang.h"
#include "BufferGFX.h"
#include "TextureGFX.h"
#include <string>
#include <vector>
#include <unordered_map>

template <>
struct std::hash<cc::gfx::ShaderInfo>
{
    typedef cc::gfx::ShaderInfo argument_type;
    typedef std::size_t result_type;
    result_type operator()(argument_type const& info) const noexcept
    {
        result_type h{};
        for (auto&& s : info.stages)
        {
            h ^= std::hash<uint32_t>{}((uint32_t)s.stage);
            h ^= std::hash<std::string>{}(s.source);
        }
        return h;
    }
};

CC_BACKEND_BEGIN

class ShaderModuleGFX;
class ProgramStateGFX;

class ProgramGFX final : public Program
{
public:
    ProgramGFX(const cc::gfx::ShaderInfo& shaderInfo);

    ~ProgramGFX() override;

    cc::gfx::Shader* getHandler() const { return _program; }
    bool isValid() const { return getHandler(); }

    const cc::gfx::ShaderInfo& getShaderInfo() const { return _info; }
    size_t getHash() const { return hash; }

    UniformLocation getUniformLocation(std::string_view uniform) const override;
    UniformLocation getUniformLocation(backend::Uniform name) const override;
    int getAttributeLocation(std::string_view name) const override;
    int getAttributeLocation(Attribute name) const override;
    int getMaxVertexLocation() const override;
    int getMaxFragmentLocation() const override;
    const std::unordered_map<std::string, AttributeBindInfo>& getActiveAttributes() const override;
    //
    std::size_t getUniformBufferSize(ShaderStage stage) const override;
    std::size_t getUniformBlockSize(const std::string& blockName) const;
    const UniformInfo& getActiveUniformInfo(ShaderStage stage, int location) const override;
    const std::unordered_map<std::string, UniformInfo>& getAllActiveUniformInfo(ShaderStage stage) const override;

    struct BlockInfoEx
    {
        std::string name;
        uint32_t size = 0;  // buffer size
        size_t index  = 0;  // index in list
        std::unordered_map<std::string, UniformInfo> members;
    };

    const std::unordered_map<std::string, BlockInfoEx>& getBlockInfoEx() const { return blockInfoEx; }
    // get default (set=0)
    const cc::gfx::DescriptorSetLayoutBindingList& getUniformLayoutBindings() const { return uniformLayoutBindings; }
    cc::gfx::DescriptorSetLayoutBindingList getUniformLayoutBindings(uint32_t set) const;

    cc::gfx::DescriptorSetLayout* createDescriptorSetLayout(
        const cc::gfx::DescriptorSetLayoutBindingList& extraBindings, uint32_t set = 0);
    cc::gfx::DescriptorSetLayout* getDefaultDescriptorSetLayout() const { return defaultDescriptorSetLayout; }
    cc::gfx::PipelineLayout* getDefaultPipelineLayout();

    ProgramStateGFX* getState(const ProgramState* key);

protected:
#if CC_ENABLE_CACHE_TEXTURE_DATA
    /**
     * In case of EGL context lost, the engine will reload shaders. Thus location of uniform may changed.
     * The engine will maintain the relationship between the original uniform location and the current active uniform
     * location.
     */
    virtual int getMappedLocation(int location) const { return location; }
    virtual int getOriginalLocation(int location) const { return location; }

    /**
     * Get all uniform locations.
     * @return All uniform locations.
     */
    virtual const std::unordered_map<std::string, int> getAllUniformsLocation() const { return {}; }
#endif

    bool generateState(const ProgramState* state);
    void removeState(const ProgramState* state);

    using SpirvCodes = std::unordered_map<cc::gfx::ShaderStageFlagBit, std::vector<uint32_t>>;

    static void initDefaultInfo();
    static ShaderModuleGFX* getShaderModule(const cc::gfx::ShaderStage& stage);
    static void computeShaderInfo(
        glslang::TProgram* program,
        cc::gfx::ShaderInfo& info,
        std::unordered_map<std::string, BlockInfoEx>& blockInfoEx);
    static void updateBlockInfoEx(
        const cc::gfx::ShaderInfo& info, std::unordered_map<std::string, BlockInfoEx>& blockInfoEx);
    static void fixForGLES2(cc::gfx::ShaderInfo& info);
    static cc::gfx::DescriptorSetLayoutBindingList computeUniformLayoutBindings(
        const cc::gfx::ShaderInfo& info, uint32_t set = 0);
    static SpirvCodes compileSpirvCodes(
        glslang::TProgram* tProgram, const std::vector<cc::gfx::ShaderStageFlagBit>& stages);
    static std::string generateShaderName(const cc::gfx::ShaderInfo& shaderInfo, void* p);
    static void addPurageListener();

    cc::gfx::Shader* _program = nullptr;
    cc::gfx::ShaderInfo _info;
    size_t hash = 0;
    cocos2d::Vector<ShaderModuleGFX*> modules;
    size_t totalUniformSize = 0;
    cc::gfx::DescriptorSetLayoutBindingList uniformLayoutBindings;
    cc::gfx::DescriptorSetLayout* defaultDescriptorSetLayout = nullptr;
    cc::gfx::PipelineLayout* defaultPipelineLayout           = nullptr;
    std::unordered_map<std::string, AttributeBindInfo> attributeInfos;
    hlookup::string_map<UniformLocation> activeUniformLocations;
    std::unordered_map<std::string, UniformInfo> activeUniformInfos;
    std::unordered_map<std::string, BlockInfoEx> blockInfoEx;
    std::unordered_map<std::string, cc::gfx::UniformSamplerTexture> samplers;
    // for ProgramState
    cocos2d::Map<void*, ProgramStateGFX*> _states;

    static cc::gfx::AttributeList builtinAttributes;
    static cc::gfx::UniformBlockList builtinUniforms;
    static cc::gfx::UniformSamplerTextureList builtinSamplerTextures;
    static cocos2d::Map<size_t, ShaderModuleGFX*> cachedModules;
    static std::unordered_map<size_t, ProgramGFX*> cachedPrograms;

    friend class ProgramState;
    friend class CommandBufferGFX;
};

class ProgramStateGFX : public Ref
{
public:
    ProgramStateGFX(ProgramGFX* program_, const cocos2d::Map<std::string, BufferGFX*>& buffers_ = {});
    ~ProgramStateGFX() override;

    bool setBuffer(const std::string& blockName, BufferGFX* buffer);
    BufferGFX* getBuffer(const std::string& blockName);
    bool setUniform(const std::string& name, const void* data, std::size_t size);
    bool setUniform(const UniformLocation& loc, const void* data, std::size_t size);
    bool setAllBuffer(const void* data, std::size_t size);
    int32_t getAllBufferOffset(const UniformLocation& loc);
    bool syncTextures(ProgramStateGFX* dst);

    // bool setTexture(const std::string& name, TextureGFX* texture, uint32_t index = 0);
    bool setTexture(const std::string& name, TextureBackend* texture, uint32_t index = 0);
    bool setTexture(const UniformLocation& loc, TextureBackend* texture, uint32_t index = 0);
    // bind to external DescriptorSet
    void bindBuffers(cc::gfx::DescriptorSet* ds, uint32_t set);
    void bindTextures(cc::gfx::DescriptorSet* ds, uint32_t set);
    // bind to internal DescriptorSet
    void bindBuffers(uint32_t set = 0);
    void bindTextures(uint32_t set = 0);

    cc::gfx::DescriptorSet* getDescriptorSet() const { return descriptorSet; }

protected:
    ProgramGFX* program                   = nullptr;
    cc::gfx::DescriptorSet* descriptorSet = nullptr;
    // { bname: buffer }
    cocos2d::Map<std::string, BufferGFX*> buffers;
    // { uname: { index: texture } }
    std::unordered_map<std::string, cocos2d::Map<uint32_t, TextureBackend*>> textures;
    std::vector<uint32_t> allBufferOffsets;
    std::map<uint32_t, std::vector<std::string>> blocksByBinding;
    std::map<uint32_t, std::vector<std::string>> sbuffersByBinding;

    friend class ProgramState;
};

CC_BACKEND_END
