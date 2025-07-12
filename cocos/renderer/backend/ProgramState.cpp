/****************************************************************************
 Copyright (c) 2018-2019 Xiamen Yaji Software Co., Ltd.
 Copyright (c) 2021-2022 Bytedance Inc.

 https://axmolengine.github.io/

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "renderer/backend/ProgramState.h"
#include "renderer/backend/Program.h"
#include "renderer/backend/Texture.h"
#include "renderer/backend/Types.h"
#include "base/CCEventDispatcher.h"
#include "base/CCEventType.h"
#include "base/CCDirector.h"
#ifdef CC_USE_GFX
#include "renderer/backend/gfx/ProgramGFX.h"
#endif

#include <algorithm>

#include "xxhash.h"

#ifdef CC_USE_METAL
    #include "glsl_optimizer.h"
#endif

CC_BACKEND_BEGIN

namespace
{
#define MAT3_SIZE 36
#define MAT4X3_SIZE 48
#define VEC3_SIZE 12
#define VEC4_SIZE 16
#define BVEC3_SIZE 3
#define BVEC4_SIZE 4
#define IVEC3_SIZE 12
#define IVEC4_SIZE 16

void convertbVec3TobVec4(const bool* src, bool* dst)
{
    dst[0] = src[0];
    dst[1] = src[1];
    dst[2] = src[2];
    dst[3] = false;
}

void convertiVec3ToiVec4(const int* src, int* dst)
{
    dst[0] = src[0];
    dst[1] = src[1];
    dst[2] = src[2];
    dst[3] = 0;
}

void convertVec3ToVec4(const float* src, float* dst)
{
    dst[0] = src[0];
    dst[1] = src[1];
    dst[2] = src[2];
    dst[3] = 0.0f;
}

void convertMat3ToMat4x3(const float* src, float* dst)
{
    dst[3] = dst[7] = dst[11] = 0.0f;
    dst[0]                    = src[0];
    dst[1]                    = src[1];
    dst[2]                    = src[2];
    dst[4]                    = src[3];
    dst[5]                    = src[4];
    dst[6]                    = src[5];
    dst[8]                    = src[6];
    dst[9]                    = src[7];
    dst[10]                   = src[8];
}
}  // namespace

// static field
std::vector<ProgramState::AutoBindingResolver*> ProgramState::_customAutoBindingResolvers;

TextureInfo::TextureInfo(std::vector<int>&& _slots, std::vector<backend::TextureBackend*>&& _textures)
    : TextureInfo(std::move(_slots), std::vector<int>(_slots.size(), 0), std::move(_textures))
{}

TextureInfo::TextureInfo(std::vector<int>&& _slots,
                         std::vector<int>&& _indexs,
                         std::vector<backend::TextureBackend*>&& _textures)
    : slots(std::move(_slots)), indexs(std::move(_indexs)), textures(std::move(_textures))
{
    retainTextures();
}

/* CLASS TextureInfo */
TextureInfo::TextureInfo(const TextureInfo& other)
{
    this->assign(other);
}

TextureInfo::TextureInfo(TextureInfo&& other)
{
    this->assign(std::move(other));
}

TextureInfo::~TextureInfo()
{
    releaseTextures();
}

void TextureInfo::retainTextures()
{
    for (auto&& texture : textures)
        CC_SAFE_RETAIN(texture);
}

void TextureInfo::releaseTextures()
{
    for (auto&& texture : textures)
        CC_SAFE_RELEASE(texture);
    textures.clear();
}

TextureInfo& TextureInfo::operator=(const TextureInfo& other) noexcept
{
    this->assign(other);
    return *this;
}

TextureInfo& TextureInfo::operator=(TextureInfo&& other) noexcept
{
    this->assign(std::move(other));
    return *this;
}

void TextureInfo::assign(const TextureInfo& other)
{
    if (this != &other)
    {
        releaseTextures();

        indexs   = other.indexs;
        slots    = other.slots;
        textures = other.textures;
        retainTextures();

#if CC_ENABLE_CACHE_TEXTURE_DATA
        location = other.location;
#endif
    }
}

void TextureInfo::assign(TextureInfo&& other)
{
    if (this != &other)
    {
        releaseTextures();

        indexs   = std::move(other.indexs);
        slots    = std::move(other.slots);
        textures = std::move(other.textures);

#if CC_ENABLE_CACHE_TEXTURE_DATA
        location       = other.location;
        other.location = -1;
#endif
    }
}

/* CLASS ProgramState */
ProgramState::ProgramState(Program* program)
{
    init(program);
}

bool ProgramState::init(Program* program)
{
    CC_SAFE_RETAIN(program);
    _program                 = program;
    _vertexLayout            = program->getVertexLayout();
    _ownVertexLayout         = false;
    _vertexUniformBufferSize = _program->getUniformBufferSize(ShaderStage::VERTEX);
    _vertexUniformBuffer     = (char*)calloc(1, _vertexUniformBufferSize);
#if defined(CC_USE_GFX)
    const auto ok = static_cast<ProgramGFX*>(_program)->generateState(this);
    CC_ASSERT(ok);
#elif defined(CC_USE_METAL)
    _fragmentUniformBufferSize = _program->getUniformBufferSize(ShaderStage::FRAGMENT);
    _fragmentUniformBuffer     = (char*)calloc(1, _fragmentUniformBufferSize);
    _uniformHashState = XXH32_createState();
#endif

#if CC_ENABLE_CACHE_TEXTURE_DATA
    _backToForegroundListener =
        EventListenerCustom::create(EVENT_RENDERER_RECREATED, [this](EventCustom*) { this->resetUniforms(); });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(_backToForegroundListener, -1);
#endif
    return true;
}

void ProgramState::resetUniforms()
{
#if CC_ENABLE_CACHE_TEXTURE_DATA
    if (_program == nullptr)
        return;

    const auto& uniformLocation = _program->getAllUniformsLocation();
    for (const auto& uniform : uniformLocation)
    {
        auto location       = uniform.second;
        auto mappedLocation = _program->getMappedLocation(location);

        // check if current location had been set before
        if (_vertexTextureInfos.find(location) != _vertexTextureInfos.end())
        {
            _vertexTextureInfos[location].location = mappedLocation;
        }
    }
#endif
}

ProgramState::~ProgramState()
{
#ifdef CC_USE_GFX
    static_cast<ProgramGFX*>(_program)->removeState(this);
#endif
#ifdef CC_USE_METAL
    XXH32_freeState(_uniformHashState);
#endif
    CC_SAFE_RELEASE(_program);
    CC_SAFE_FREE(_vertexUniformBuffer);
    CC_SAFE_FREE(_fragmentUniformBuffer);

#if CC_ENABLE_CACHE_TEXTURE_DATA
    Director::getInstance()->getEventDispatcher()->removeEventListener(_backToForegroundListener);
#endif

    if (_ownVertexLayout)
        CC_SAFE_DELETE(_vertexLayout);
}

ProgramState* ProgramState::clone() const
{
    ProgramState* cp          = new ProgramState(_program);
    cp->_vertexTextureInfos   = _vertexTextureInfos;
    cp->_fragmentTextureInfos = _fragmentTextureInfos;
    memcpy(cp->_vertexUniformBuffer, _vertexUniformBuffer, _vertexUniformBufferSize);

    cp->_ownVertexLayout = _ownVertexLayout;
    cp->_vertexLayout    = !_ownVertexLayout ? _vertexLayout : new VertexLayout(*_vertexLayout);
#if defined(CC_USE_GFX)
    const auto p = static_cast<ProgramGFX*>(_program);
    p->generateState(cp);
    const auto stateGFX = p->getState(cp);
    CC_ASSERT(stateGFX);
    stateGFX->setAllBuffer(_vertexUniformBuffer, _vertexUniformBufferSize);
    stateGFX->textures = p->getState(this)->textures;
#elif defined(CC_USE_METAL)
    memcpy(cp->_fragmentUniformBuffer, _fragmentUniformBuffer, _fragmentUniformBufferSize);
#endif
    cp->_uniformID = _uniformID;
    return cp;
}

backend::UniformLocation ProgramState::getUniformLocation(backend::Uniform name) const
{
    return _program->getUniformLocation(name);
}

backend::UniformLocation ProgramState::getUniformLocation(std::string_view uniform) const
{
    return _program->getUniformLocation(uniform);
}

void ProgramState::setCallbackUniform(const backend::UniformLocation& uniformLocation, const UniformCallback& callback)
{
    _callbackUniforms[uniformLocation] = callback;
}

void ProgramState::setUniform(const backend::UniformLocation& uniformLocation, const void* data, std::size_t size)
{
#ifdef CC_USE_GFX
    const auto p = static_cast<ProgramGFX*>(_program);
    CC_ASSERT(p->isValid());
    const auto location = uniformLocation.location[0];
    const auto offset   = uniformLocation.location[1];
    const auto state    = p->getState(this);
    CC_ASSERT(state);
    if (!state)
        return;
    if (!state->setUniform(uniformLocation, data, size))
    {
#if CC_DEBUG
        log("%s: failed, loc=%d, size=%d, offset=%d", __FUNCTION__, location, (int)size, offset);
        CCASSERT(false, "failed");
#endif
    }
    const auto allOffset = state->getAllBufferOffset(uniformLocation);
    if (allOffset + size > _vertexUniformBufferSize || allOffset > _vertexUniformBufferSize ||
        size > _vertexUniformBufferSize)
    {
#if CC_DEBUG
        log("%s: invalid parameters, loc=%d, size=%d, offset=%d", __FUNCTION__, location, (int)size, (int)allOffset);
        CCASSERT(false, "invalid parameters");
#endif
        return;
    }
    if (allOffset < 0)
    {
#if CC_DEBUG
        log("%s: invalid uniform location, [0]=%d, [1]=%d", __FUNCTION__, location, (int)offset);
        CCASSERT(false, "invalid uniform location");
#endif
        return;
    }
    memcpy(_vertexUniformBuffer + allOffset, data, size);
#else
    switch (uniformLocation.shaderStage)
    {
    case backend::ShaderStage::VERTEX:
        setVertexUniform(uniformLocation.location[0], data, size, uniformLocation.location[1]);
        break;
    case backend::ShaderStage::FRAGMENT:
        setFragmentUniform(uniformLocation.location[1], data, size);
        break;
    case backend::ShaderStage::VERTEX_AND_FRAGMENT:
        setVertexUniform(uniformLocation.location[0], data, size, uniformLocation.location[1]);
        setFragmentUniform(uniformLocation.location[1], data, size);
        break;
    default:
        break;
    }
#endif
    _uniformID = -1;
}

#if !defined(CC_USE_GFX) && defined(CC_USE_METAL)
void ProgramState::convertAndCopyUniformData(const backend::UniformInfo& uniformInfo,
                                             const void* srcData,
                                             std::size_t srcSize,
                                             void* buffer)
{
    auto basicType      = static_cast<glslopt_basic_type>(uniformInfo.type);
    char* convertedData = new char[uniformInfo.size];
    memset(convertedData, 0, uniformInfo.size);
    int offset = 0;
    switch (basicType)
    {
    case kGlslTypeFloat:
    {
        if (uniformInfo.isMatrix)
        {
            for (int i = 0; i < uniformInfo.count; i++)
            {
                if (offset >= srcSize)
                    break;

                convertMat3ToMat4x3((float*)srcData + offset, (float*)convertedData + i * MAT4X3_SIZE);
                offset += MAT3_SIZE;
            }
        }
        else
        {
            for (int i = 0; i < uniformInfo.count; i++)
            {
                if (offset >= srcSize)
                    break;

                convertVec3ToVec4((float*)srcData + offset, (float*)convertedData + i * VEC4_SIZE);
                offset += VEC3_SIZE;
            }
        }
        break;
    }
    case kGlslTypeBool:
    {
        for (int i = 0; i < uniformInfo.count; i++)
        {
            if (offset >= srcSize)
                break;

            convertbVec3TobVec4((bool*)srcData + offset, (bool*)convertedData + i * BVEC4_SIZE);
            offset += BVEC3_SIZE;
        }
        break;
    }
    case kGlslTypeInt:
    {
        for (int i = 0; i < uniformInfo.count; i++)
        {
            if (offset >= srcSize)
                break;

            convertiVec3ToiVec4((int*)srcData + offset, (int*)convertedData + i * IVEC4_SIZE);
            offset += IVEC3_SIZE;
        }
        break;
    }
    default:
        CC_ASSERT(false);
        break;
    }

    memcpy((char*)buffer + uniformInfo.location, convertedData, uniformInfo.size);
    CC_SAFE_DELETE_ARRAY(convertedData);
}
#endif

void ProgramState::setVertexUniform(int location, const void* data, std::size_t size, std::size_t offset)
{
    if (location < 0)
        return;

// float3 etc in Metal has both sizeof and alignment same as float4, need convert to correct laytout
#if !defined(CC_USE_GFX) && defined(CC_USE_METAL)
    const auto& uniformInfo = _program->getActiveUniformInfo(ShaderStage::VERTEX, location);
    if (uniformInfo.needConvert)
    {
        convertAndCopyUniformData(uniformInfo, data, size, _vertexUniformBuffer);
    }
    else
    {
        memcpy(_vertexUniformBuffer + location, data, size);
    }
#else
    if (offset + size > _vertexUniformBufferSize ||
        offset > _vertexUniformBufferSize ||
        size > _vertexUniformBufferSize)
    {
#if CC_DEBUG
        log("setVertexUniform: %d, %d, %d", location, (int)size, (int)offset);
        CCASSERT(false, "setVertexUniform: invalid parameters");
#endif
    }
    memcpy(_vertexUniformBuffer + offset, data, size);
#endif
    _uniformID = -1;
}

void ProgramState::setFragmentUniform(int location, const void* data, std::size_t size)
{
    if (location < 0)
        return;

// float3 etc in Metal has both sizeof and alignment same as float4, need convert to correct laytout
#if !defined(CC_USE_GFX) && defined(CC_USE_METAL)
    const auto& uniformInfo = _program->getActiveUniformInfo(ShaderStage::FRAGMENT, location);
    if (uniformInfo.needConvert)
    {
        convertAndCopyUniformData(uniformInfo, data, size, _fragmentUniformBuffer);
    }
    else
    {
        memcpy(_fragmentUniformBuffer + location, data, size);
    }
#endif
}

void ProgramState::setVertexAttrib(std::string_view name,
    std::size_t index,
    VertexFormat format,
    std::size_t offset,
    bool needToBeNormallized)
{
    ensureVertexLayoutMutable();

    _vertexLayout->setAttribute(name, index, format, offset, needToBeNormallized);
}

void ProgramState::setVertexStride(uint32_t stride)
{
    ensureVertexLayoutMutable();
    _vertexLayout->setStride(stride);
}

void ProgramState::setVertexLayout(const VertexLayout& vertexLayout) {
    ensureVertexLayoutMutable();
    *_vertexLayout = vertexLayout;
}

void ProgramState::validateSharedVertexLayout(std::function<void(Program*)> fnValidate)
{
    if (!_ownVertexLayout && !_vertexLayout->isValid())
        fnValidate(_program);
}

void ProgramState::ensureVertexLayoutMutable()
{
    if (!_ownVertexLayout)
    {
        _vertexLayout = new VertexLayout();
        _ownVertexLayout = true;
    }
}

uint32_t ProgramState::getUniformID()
{
    if (_uniformID == -1)
        updateUniformID();
    return _uniformID;
}

void ProgramState::updateUniformID(int uniformID)
{
    if (uniformID == -1)
    {
#ifdef CC_USE_METAL
        XXH32_reset(_uniformHashState, 0);
        XXH32_update(_uniformHashState, _vertexUniformBuffer, _vertexUniformBufferSize);
        XXH32_update(_uniformHashState, _fragmentUniformBuffer, _fragmentUniformBufferSize);
        _uniformID = XXH32_digest(_uniformHashState);
#else
        _uniformID = XXH32(_vertexUniformBuffer, _vertexUniformBufferSize, 0);
#endif
    }
    else
    {
        _uniformID = uniformID;
    }
}

void ProgramState::setTexture(backend::TextureBackend* texture)
{
    for (int slot = 0; slot < texture->getCount() && slot < CC_META_TEXTURES; ++slot)
    {
        auto location = getUniformLocation((backend::Uniform)(backend::Uniform::TEXTURE + slot));
        setTexture(location, slot, slot, texture);
    }
}

void ProgramState::setTexture(const backend::UniformLocation& uniformLocation,
                              int slot,
                              backend::TextureBackend* texture)
{
    setTexture(uniformLocation, slot, 0, texture);
}

void ProgramState::setTexture(const backend::UniformLocation& uniformLocation,
                              int slot,
                              int index,
                              backend::TextureBackend* texture)
{
#ifdef CC_USE_GFX
    const auto p = static_cast<ProgramGFX*>(_program);
    CC_ASSERT(p->isValid());
    const auto state = p->getState(this);
    CC_ASSERT(state);
    if (state)
    {
        // slot is replaced by location[0]
        const bool ok = state->setTexture(uniformLocation, texture, /*slot*/ 0);
        if (!ok)
        {
            /*
            log("%s: %s failed, location=%d,%d, slot=%d, texture=0x%x",
                __FUNCTION__,
                p->getShaderInfo().name.c_str(),
                uniformLocation.location[0],
                uniformLocation.location[1],
                slot,
                texture);
            */
        }
    }
#endif
    switch (uniformLocation.shaderStage)
    {
    case backend::ShaderStage::VERTEX:
        setTexture(uniformLocation.location[0], slot, index, texture, _vertexTextureInfos);
        break;
    case backend::ShaderStage::FRAGMENT:
        setTexture(uniformLocation.location[1], slot, index, texture, _fragmentTextureInfos);
        break;
    case backend::ShaderStage::VERTEX_AND_FRAGMENT:
        setTexture(uniformLocation.location[0], slot, index, texture, _vertexTextureInfos);
        setTexture(uniformLocation.location[1], slot, index, texture, _fragmentTextureInfos);
        break;
    default:
        break;
    }
}

void ProgramState::setTextureArray(const backend::UniformLocation& uniformLocation,
                                   std::vector<int> slots,
                                   std::vector<backend::TextureBackend*> textures)
{
#ifdef CC_USE_GFX
    for (int i = 0; i < std::min(slots.size(), textures.size()); ++i)
    {
        setTexture(uniformLocation, slots.at(i), textures.at(i));
    }
#endif
    switch (uniformLocation.shaderStage)
    {
    case backend::ShaderStage::VERTEX:
        setTextureArray(uniformLocation.location[0], std::move(slots), std::move(textures), _vertexTextureInfos);
        break;
    case backend::ShaderStage::FRAGMENT:
        setTextureArray(uniformLocation.location[1], std::move(slots), std::move(textures), _fragmentTextureInfos);
        break;
    case backend::ShaderStage::VERTEX_AND_FRAGMENT:
        setTextureArray(uniformLocation.location[0], std::move(slots), std::move(textures), _vertexTextureInfos);
        setTextureArray(uniformLocation.location[1], std::move(slots), std::move(textures), _fragmentTextureInfos);
        break;
    default:
        break;
    }
}

void ProgramState::setTexture(int location,
                              int slot,
                              int index,
                              backend::TextureBackend* texture,
                              std::unordered_map<int, TextureInfo>& textureInfo)
{
    if (location < 0)
        return;

    auto& info = textureInfo[location];
    info       = {{slot}, {index}, {texture}};

#if CC_ENABLE_CACHE_TEXTURE_DATA
    info.location = location;
#endif
}

void ProgramState::setTextureArray(int location,
                                   std::vector<int> slots,
                                   std::vector<backend::TextureBackend*> textures,
                                   std::unordered_map<int, TextureInfo>& textureInfo)
{
    assert(slots.size() == textures.size());

    auto& info = textureInfo[location];
    info       = {std::move(slots), std::move(textures)};

#if CC_ENABLE_CACHE_TEXTURE_DATA
    info.location = location;
#endif
}

void ProgramState::setParameterAutoBinding(std::string_view uniform, std::string_view autoBinding)
{
    _autoBindings.emplace(uniform, autoBinding);
    applyAutoBinding(uniform, autoBinding);
}

void ProgramState::applyAutoBinding(std::string_view uniformName, std::string_view autoBinding)
{
    for (const auto resolver : _customAutoBindingResolvers)
    {
        if (resolver->resolveAutoBinding(this, uniformName, autoBinding))
            break;
    }
}

ProgramState::AutoBindingResolver::AutoBindingResolver()
{
    _customAutoBindingResolvers.emplace_back(this);
}

ProgramState::AutoBindingResolver::~AutoBindingResolver()
{
    auto& list = _customAutoBindingResolvers;
    list.erase(std::remove(list.begin(), list.end(), this), list.end());
}

void ProgramState::getVertexUniformBuffer(char** buffer, std::size_t& size) const
{
    *buffer = _vertexUniformBuffer;
    size    = _vertexUniformBufferSize;
}

void ProgramState::getFragmentUniformBuffer(char** buffer, std::size_t& size) const
{
    *buffer = _fragmentUniformBuffer;
    size    = _fragmentUniformBufferSize;
}

CC_BACKEND_END
