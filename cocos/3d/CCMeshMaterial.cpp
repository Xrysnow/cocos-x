/****************************************************************************
 Copyright (c) 2014-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

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

#include "3d/CCMeshMaterial.h"
#include "3d/CCMesh.h"
#include "platform/CCFileUtils.h"
#include "renderer/CCTexture2D.h"
#include "base/CCDirector.h"
#include "base/CCEventType.h"
#include "base/CCConfiguration.h"
#include "renderer/backend/ProgramState.h"
#include "renderer/ccShaders.h"
#include "renderer/CCPass.h"

NS_CC_BEGIN

MeshMaterialCache* MeshMaterialCache::_cacheInstance = nullptr;

std::unordered_map<std::string, MeshMaterial*> MeshMaterial::_materials;
MeshMaterial* MeshMaterial::_unLitMaterial         = nullptr;
MeshMaterial* MeshMaterial::_unLitNoTexMaterial    = nullptr;
MeshMaterial* MeshMaterial::_vertexLitMaterial     = nullptr;
MeshMaterial* MeshMaterial::_diffuseMaterial       = nullptr;
MeshMaterial* MeshMaterial::_diffuseNoTexMaterial  = nullptr;
MeshMaterial* MeshMaterial::_bumpedDiffuseMaterial = nullptr;

MeshMaterial* MeshMaterial::_unLitMaterialSkin         = nullptr;
MeshMaterial* MeshMaterial::_vertexLitMaterialSkin     = nullptr;
MeshMaterial* MeshMaterial::_diffuseMaterialSkin       = nullptr;
MeshMaterial* MeshMaterial::_bumpedDiffuseMaterialSkin = nullptr;

MeshMaterial* MeshMaterial::_quadTextureMaterial = nullptr;
MeshMaterial* MeshMaterial::_quadColorMaterial = nullptr;

backend::ProgramState* MeshMaterial::_unLitMaterialProgState         = nullptr;
backend::ProgramState* MeshMaterial::_unLitNoTexMaterialProgState    = nullptr;
backend::ProgramState* MeshMaterial::_vertexLitMaterialProgState     = nullptr;
backend::ProgramState* MeshMaterial::_diffuseMaterialProgState       = nullptr;
backend::ProgramState* MeshMaterial::_diffuseNoTexMaterialProgState  = nullptr;
backend::ProgramState* MeshMaterial::_bumpedDiffuseMaterialProgState = nullptr;

backend::ProgramState* MeshMaterial::_unLitMaterialSkinProgState         = nullptr;
backend::ProgramState* MeshMaterial::_vertexLitMaterialSkinProgState     = nullptr;
backend::ProgramState* MeshMaterial::_diffuseMaterialSkinProgState       = nullptr;
backend::ProgramState* MeshMaterial::_bumpedDiffuseMaterialSkinProgState = nullptr;

backend::ProgramState* MeshMaterial::_quadTextureMaterialProgState            = nullptr;
backend::ProgramState* MeshMaterial::_quadColorMaterialProgState            = nullptr;

void MeshMaterial::createBuiltInMaterial()
{
    auto* program               = backend::Program::getBuiltinProgram(backend::ProgramType::SKINPOSITION_TEXTURE_3D);
    _unLitMaterialSkinProgState = new backend::ProgramState(program);
    _unLitMaterialSkin          = new MeshMaterial();
    if (_unLitMaterialSkin && _unLitMaterialSkin->initWithProgramState(_unLitMaterialSkinProgState))
    {
        _unLitMaterialSkin->_type = MeshMaterial::MaterialType::UNLIT;
    }

    program = backend::Program::getBuiltinProgram(backend::ProgramType::SKINPOSITION_NORMAL_TEXTURE_3D);
    _diffuseMaterialSkinProgState = new backend::ProgramState(program);
    _diffuseMaterialSkin          = new MeshMaterial();
    if (_diffuseMaterialSkin && _diffuseMaterialSkin->initWithProgramState(_diffuseMaterialSkinProgState))
    {
        _diffuseMaterialSkin->_type = MeshMaterial::MaterialType::DIFFUSE;
    }

    program                   = backend::Program::getBuiltinProgram(backend::ProgramType::POSITION_NORMAL_TEXTURE_3D);
    _diffuseMaterialProgState = new backend::ProgramState(program);
    _diffuseMaterial          = new MeshMaterial();
    if (_diffuseMaterial && _diffuseMaterial->initWithProgramState(_diffuseMaterialProgState))
    {
        _diffuseMaterial->_type = MeshMaterial::MaterialType::DIFFUSE;
    }

    program                 = backend::Program::getBuiltinProgram(backend::ProgramType::POSITION_TEXTURE_3D);
    _unLitMaterialProgState = new backend::ProgramState(program);
    _unLitMaterial          = new MeshMaterial();
    if (_unLitMaterial && _unLitMaterial->initWithProgramState(_unLitMaterialProgState))
    {
        _unLitMaterial->_type = MeshMaterial::MaterialType::UNLIT;
    }

    program                      = backend::Program::getBuiltinProgram(backend::ProgramType::POSITION_3D);
    _unLitNoTexMaterialProgState = new backend::ProgramState(program);
    _unLitNoTexMaterial          = new MeshMaterial();
    if (_unLitNoTexMaterial && _unLitNoTexMaterial->initWithProgramState(_unLitNoTexMaterialProgState))
    {
        _unLitNoTexMaterial->_type = MeshMaterial::MaterialType::UNLIT_NOTEX;
    }

    program                        = backend::Program::getBuiltinProgram(backend::ProgramType::POSITION_NORMAL_3D);
    _diffuseNoTexMaterialProgState = new backend::ProgramState(program);
    _diffuseNoTexMaterial          = new MeshMaterial();
    if (_diffuseNoTexMaterial && _diffuseNoTexMaterial->initWithProgramState(_diffuseNoTexMaterialProgState))
    {
        _diffuseNoTexMaterial->_type = MeshMaterial::MaterialType::DIFFUSE_NOTEX;
    }

    program = backend::Program::getBuiltinProgram(backend::ProgramType::POSITION_BUMPEDNORMAL_TEXTURE_3D);
    _bumpedDiffuseMaterialProgState = new backend::ProgramState(program);
    _bumpedDiffuseMaterial          = new MeshMaterial();
    if (_bumpedDiffuseMaterial && _bumpedDiffuseMaterial->initWithProgramState(_bumpedDiffuseMaterialProgState))
    {
        _bumpedDiffuseMaterial->_type = MeshMaterial::MaterialType::BUMPED_DIFFUSE;
    }

    program = backend::Program::getBuiltinProgram(backend::ProgramType::SKINPOSITION_BUMPEDNORMAL_TEXTURE_3D);
    _bumpedDiffuseMaterialSkinProgState = new backend::ProgramState(program);
    _bumpedDiffuseMaterialSkin          = new MeshMaterial();
    if (_bumpedDiffuseMaterialSkin &&
        _bumpedDiffuseMaterialSkin->initWithProgramState(_bumpedDiffuseMaterialSkinProgState))
    {
        _bumpedDiffuseMaterialSkin->_type = MeshMaterial::MaterialType::BUMPED_DIFFUSE;
    }

    program = backend::Program::getBuiltinProgram(backend::ProgramType::QUAD_TEXTURE_2D);
    _quadTextureMaterialProgState = new backend::ProgramState(program);
    _quadTextureMaterial          = new MeshMaterial();
    if (_quadTextureMaterial && _quadTextureMaterial->initWithProgramState(_quadTextureMaterialProgState))
    {
        _quadTextureMaterial->_type = MeshMaterial::MaterialType::QUAD_TEXTURE;
    }

    program = backend::Program::getBuiltinProgram(backend::ProgramType::QUAD_COLOR_2D);
    _quadColorMaterialProgState = new backend::ProgramState(program);
    _quadColorMaterial          = new MeshMaterial();
    if (_quadColorMaterial && _quadColorMaterial->initWithProgramState(_quadColorMaterialProgState))
    {
        _quadColorMaterial->_type = MeshMaterial::MaterialType::QUAD_COLOR;
    }
}

void MeshMaterial::releaseBuiltInMaterial()
{
    CC_SAFE_RELEASE_NULL(_unLitMaterial);
    CC_SAFE_RELEASE_NULL(_unLitMaterialSkin);

    CC_SAFE_RELEASE_NULL(_unLitNoTexMaterial);
    CC_SAFE_RELEASE_NULL(_vertexLitMaterial);
    CC_SAFE_RELEASE_NULL(_diffuseMaterial);
    CC_SAFE_RELEASE_NULL(_diffuseNoTexMaterial);
    CC_SAFE_RELEASE_NULL(_bumpedDiffuseMaterial);

    CC_SAFE_RELEASE_NULL(_vertexLitMaterialSkin);
    CC_SAFE_RELEASE_NULL(_diffuseMaterialSkin);
    CC_SAFE_RELEASE_NULL(_bumpedDiffuseMaterialSkin);
    // release program states
    CC_SAFE_RELEASE_NULL(_unLitMaterialProgState);
    CC_SAFE_RELEASE_NULL(_unLitNoTexMaterialProgState);
    CC_SAFE_RELEASE_NULL(_vertexLitMaterialProgState);
    CC_SAFE_RELEASE_NULL(_diffuseMaterialProgState);
    CC_SAFE_RELEASE_NULL(_diffuseNoTexMaterialProgState);
    CC_SAFE_RELEASE_NULL(_bumpedDiffuseMaterialProgState);

    CC_SAFE_RELEASE_NULL(_unLitMaterialSkinProgState);
    CC_SAFE_RELEASE_NULL(_vertexLitMaterialSkinProgState);
    CC_SAFE_RELEASE_NULL(_diffuseMaterialSkinProgState);
    CC_SAFE_RELEASE_NULL(_bumpedDiffuseMaterialSkinProgState);
}

void MeshMaterial::releaseCachedMaterial()
{
    for (auto&& it : _materials)
    {
        if (it.second)
            it.second->release();
    }
    _materials.clear();
}

Material* MeshMaterial::clone() const
{
    auto material = new MeshMaterial();

    material->_renderState = _renderState;

    for (const auto& technique : _techniques)
    {
        auto t = technique->clone();
        t->setMaterial(material);
        for (ssize_t i = 0; i < t->getPassCount(); i++)
        {
            t->getPassByIndex(i)->setTechnique(t);
        }
        material->_techniques.pushBack(t);
    }

    // current technique
    auto name                   = _currentTechnique->getName();
    material->_currentTechnique = material->getTechniqueByName(name);
    material->_type             = _type;
    material->autorelease();

    return material;
}

MeshMaterial* MeshMaterial::createBuiltInMaterial(MaterialType type, bool skinned)
{
    /////
    if (_diffuseMaterial == nullptr)
        createBuiltInMaterial();

    MeshMaterial* material = nullptr;
    switch (type)
    {
    case MeshMaterial::MaterialType::UNLIT:
        material = skinned ? _unLitMaterialSkin : _unLitMaterial;
        break;

    case MeshMaterial::MaterialType::UNLIT_NOTEX:
        material = _unLitNoTexMaterial;
        break;

    case MeshMaterial::MaterialType::VERTEX_LIT:
        CCASSERT(0, "not implemented");
        break;

    case MeshMaterial::MaterialType::DIFFUSE:
        material = skinned ? _diffuseMaterialSkin : _diffuseMaterial;
        break;

    case MeshMaterial::MaterialType::DIFFUSE_NOTEX:
        material = _diffuseNoTexMaterial;
        break;

    case MeshMaterial::MaterialType::BUMPED_DIFFUSE:
        material = skinned ? _bumpedDiffuseMaterialSkin : _bumpedDiffuseMaterial;
        break;

    case MeshMaterial::MaterialType::QUAD_TEXTURE:
        material = _quadTextureMaterial;
        break;

    case MeshMaterial::MaterialType::QUAD_COLOR:
        material = _quadColorMaterial;
        break;

    default:
        break;
    }
    if (material)
        return (MeshMaterial*)material->clone();

    return nullptr;
}

MeshMaterial* MeshMaterial::createWithFilename(std::string_view path)
{
    auto validfilename = FileUtils::getInstance()->fullPathForFilename(path);
    if (!validfilename.empty())
    {
        auto it = _materials.find(validfilename);
        if (it != _materials.end())
            return (MeshMaterial*)it->second->clone();

        auto material = new MeshMaterial();
        if (material->initWithFile(path))
        {
            material->_type           = MeshMaterial::MaterialType::CUSTOM;
            _materials[validfilename] = material;

            return (MeshMaterial*)material->clone();
        }
        CC_SAFE_DELETE(material);
    }
    return nullptr;
}

MeshMaterial* MeshMaterial::createWithProgramState(backend::ProgramState* programState)
{
    CCASSERT(programState, "Invalid program state.");

    auto mat = new MeshMaterial();
    if (mat->initWithProgramState(programState))
    {
        mat->_type = MeshMaterial::MaterialType::CUSTOM;
        mat->autorelease();
        return mat;
    }
    CC_SAFE_DELETE(mat);
    return nullptr;
}

void MeshMaterial::setTexture(Texture2D* tex, NTextureData::Usage usage)
{
    const auto& passes = getTechnique()->getPasses();
    for (auto&& pass : passes)
    {
        pass->setUniformTexture(0, tex->getBackendTexture());
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

MeshMaterialCache::MeshMaterialCache() {}

MeshMaterialCache::~MeshMaterialCache()
{
    removeAllMeshMaterial();
}

MeshMaterialCache* MeshMaterialCache::getInstance()
{
    if (!_cacheInstance)
    {
        _cacheInstance = new MeshMaterialCache();
    }

    return _cacheInstance;
}

void MeshMaterialCache::destroyInstance()
{
    if (_cacheInstance)
    {
        CC_SAFE_DELETE(_cacheInstance);
    }
}

bool MeshMaterialCache::addMeshMaterial(std::string_view key, Texture2D* texture)
{
    auto itr = _materials.find(key);
    if (itr == _materials.end())
    {
        CC_SAFE_RETAIN(texture);
        _materials.emplace(key, texture);
        return true;
    }
    return false;
}

Texture2D* MeshMaterialCache::getMeshMaterial(std::string_view key)
{
    auto itr = _materials.find(key);
    if (itr != _materials.end())
    {
        return itr->second;
    }
    return nullptr;
}

void MeshMaterialCache::removeAllMeshMaterial()
{
    for (auto&& itr : _materials)
    {
        CC_SAFE_RELEASE_NULL(itr.second);
    }
    _materials.clear();
}
void MeshMaterialCache::removeUnusedMeshMaterial()
{
    for (auto it = _materials.cbegin(), itCend = _materials.cend(); it != itCend; /* nothing */)
    {
        auto value = it->second;
        if (value->getReferenceCount() == 1)
        {
            CCLOG("cocos2d: MeshMaterialCache: removing unused mesh renderer materials.");

            value->release();
            it = _materials.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

NS_CC_END
