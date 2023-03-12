#include "UtilsGFX.h"
#include "ProgramGFX.h"
#include "renderer/backend/Types.h"
#include "gfx/backend/gfx-base/GFXDef-common.h"
#include "glslang/glslang/Public/ShaderLang.h"
#include "glslang/Include/ResourceLimits.h"
#include "SPIRV/GlslangToSpv.h"
#include "SPIRV/Logger.h"
#include "SPIRV/SpvTools.h"
#include "spirv_cross/spirv_glsl.hpp"

CC_BACKEND_BEGIN

cc::gfx::Format UtilsGFX::toAttributeType(VertexFormat vertexFormat)
{
    using cc::gfx::Format;
    switch (vertexFormat)
    {
    case VertexFormat::FLOAT4:
        return Format::RGBA32F;
    case VertexFormat::FLOAT3:
        return Format::RGB32F;
    case VertexFormat::FLOAT2:
        return Format::RG32F;
    case VertexFormat::FLOAT:
        return Format::R32F;
    case VertexFormat::INT4:
        return Format::RGBA32I;
    case VertexFormat::INT3:
        return Format::RGB32I;
    case VertexFormat::INT2:
        return Format::RG32I;
    case VertexFormat::INT:
        return Format::R32I;
    case VertexFormat::USHORT4:
        return Format::RGBA16I;
    case VertexFormat::USHORT2:
        return Format::RG16I;
    case VertexFormat::UBYTE4:
        return Format::RGBA8;
    default:
        break;
    }
    return Format::RGBA32F;
}

uint32_t UtilsGFX::getUniformStd140Alignment(cc::gfx::Type type, uint32_t count)
{
    constexpr uint32_t N  = 4;
    constexpr uint32_t N4 = 4 * N;
    if (count == 0)
    {
        switch (type)
        {
        case cc::gfx::Type::UNKNOWN:
            return 0;
        case cc::gfx::Type::BOOL:
            return N;
        case cc::gfx::Type::BOOL2:
            return 2 * N;
        case cc::gfx::Type::BOOL3:
            return 4 * N;
        case cc::gfx::Type::BOOL4:
            return 4 * N;
        case cc::gfx::Type::INT:
            return N;
        case cc::gfx::Type::INT2:
            return 2 * N;
        case cc::gfx::Type::INT3:
            return 4 * N;
        case cc::gfx::Type::INT4:
            return 4 * N;
        case cc::gfx::Type::UINT:
            return N;
        case cc::gfx::Type::UINT2:
            return 2 * N;
        case cc::gfx::Type::UINT3:
            return 4 * N;
        case cc::gfx::Type::UINT4:
            return 4 * N;
        case cc::gfx::Type::FLOAT:
            return N;
        case cc::gfx::Type::FLOAT2:
            return 2 * N;
        case cc::gfx::Type::FLOAT3:
            return 4 * N;
        case cc::gfx::Type::FLOAT4:
            return 4 * N;
        case cc::gfx::Type::MAT2:
            return 2 * N;
        case cc::gfx::Type::MAT2X3:
            return 4 * N;
        case cc::gfx::Type::MAT2X4:
            return 4 * N;
        case cc::gfx::Type::MAT3X2:
            return 2 * N;
        case cc::gfx::Type::MAT3:
            return 4 * N;
        case cc::gfx::Type::MAT3X4:
            return 4 * N;
        case cc::gfx::Type::MAT4X2:
            return 2 * N;
        case cc::gfx::Type::MAT4X3:
            return 4 * N;
        case cc::gfx::Type::MAT4:
            return 4 * N;
        default:;
        }
        return 0;
    }
    else
    {
        const auto base = getUniformStd140Alignment(type, 0);
        return std::max(base, N4);
    }
}

uint32_t UtilsGFX::getUniformStd140Size(cc::gfx::Type type, uint32_t count)
{
    constexpr uint32_t N  = 4;
    constexpr uint32_t N4 = 4 * N;
    if (count == 0)
    {
        switch (type)
        {
        case cc::gfx::Type::UNKNOWN:
            return 0;
        case cc::gfx::Type::BOOL:
            return N;
        case cc::gfx::Type::BOOL2:
            return 2 * N;
        case cc::gfx::Type::BOOL3:
            return 3 * N;
        case cc::gfx::Type::BOOL4:
            return 4 * N;
        case cc::gfx::Type::INT:
            return N;
        case cc::gfx::Type::INT2:
            return 2 * N;
        case cc::gfx::Type::INT3:
            return 3 * N;
        case cc::gfx::Type::INT4:
            return 4 * N;
        case cc::gfx::Type::UINT:
            return N;
        case cc::gfx::Type::UINT2:
            return 2 * N;
        case cc::gfx::Type::UINT3:
            return 3 * N;
        case cc::gfx::Type::UINT4:
            return 4 * N;
        case cc::gfx::Type::FLOAT:
            return N;
        case cc::gfx::Type::FLOAT2:
            return 2 * N;
        case cc::gfx::Type::FLOAT3:
            return 3 * N;
        case cc::gfx::Type::FLOAT4:
            return 4 * N;
        case cc::gfx::Type::MAT2:
            return N4 * 2;
        case cc::gfx::Type::MAT2X3:
            return N4 * 2;
        case cc::gfx::Type::MAT2X4:
            return N4 * 2;
        case cc::gfx::Type::MAT3X2:
            return N4 * 3;
        case cc::gfx::Type::MAT3:
            return N4 * 3;
        case cc::gfx::Type::MAT3X4:
            return N4 * 3;
        case cc::gfx::Type::MAT4X2:
            return N4 * 4;
        case cc::gfx::Type::MAT4X3:
            return N4 * 4;
        case cc::gfx::Type::MAT4:
            return N4 * 4;
        default:;
        }
        return 0;
    }
    else
    {
        switch (type)
        {
        case cc::gfx::Type::UNKNOWN:
            return 0;
        case cc::gfx::Type::BOOL:
        case cc::gfx::Type::BOOL2:
        case cc::gfx::Type::BOOL3:
        case cc::gfx::Type::BOOL4:
        case cc::gfx::Type::INT:
        case cc::gfx::Type::INT2:
        case cc::gfx::Type::INT3:
        case cc::gfx::Type::INT4:
        case cc::gfx::Type::UINT:
        case cc::gfx::Type::UINT2:
        case cc::gfx::Type::UINT3:
        case cc::gfx::Type::UINT4:
        case cc::gfx::Type::FLOAT:
        case cc::gfx::Type::FLOAT2:
        case cc::gfx::Type::FLOAT3:
        case cc::gfx::Type::FLOAT4:
            return N4 * count;
        case cc::gfx::Type::MAT2:
            return N4 * count * 2;
        case cc::gfx::Type::MAT2X3:
            return N4 * count * 2;
        case cc::gfx::Type::MAT2X4:
            return N4 * count * 2;
        case cc::gfx::Type::MAT3X2:
            return N4 * count * 3;
        case cc::gfx::Type::MAT3:
            return N4 * count * 3;
        case cc::gfx::Type::MAT3X4:
            return N4 * count * 3;
        case cc::gfx::Type::MAT4X2:
            return N4 * count * 4;
        case cc::gfx::Type::MAT4X3:
            return N4 * count * 4;
        case cc::gfx::Type::MAT4:
            return N4 * count * 4;
        default:;
        }
        return 0;
    }
}

uint32_t UtilsGFX::getUniformStd140Offset(cc::gfx::Type type, uint32_t count, uint32_t base)
{
    const auto align = getUniformStd140Alignment(type, count);
    if (base / align * align < base)
        base = (base / align + 1) * align;
    return base;
}

uint32_t UtilsGFX::getUniformStructStd140Size(uint32_t totalSize)
{
    const auto upper = (totalSize / 16 + 1) * 16;
    return (upper - totalSize == 16) ? totalSize : upper;
}

cc::gfx::Filter UtilsGFX::toMagFilter(SamplerFilter magFilter)
{
    using cc::gfx::Filter;
    Filter ret = Filter::LINEAR;
    switch (magFilter)
    {
    case SamplerFilter::LINEAR:
        ret = Filter::LINEAR;
        break;
    case SamplerFilter::NEAREST:
        ret = Filter::POINT;
        break;
    default:
        break;
    }
    return ret;
}

cc::gfx::Filter UtilsGFX::toMinFilter(SamplerFilter minFilter, bool hasMipmaps, bool isPow2)
{
    using cc::gfx::Filter;
    if (hasMipmaps && !isPow2)
    {
        CCLOG(
            "Change minification filter to either NEAREST or LINEAR since non-power-of-two texture occur in %s %s %d",
            __FILE__,
            __FUNCTION__,
            __LINE__);
        if (SamplerFilter::LINEAR == minFilter)
            return Filter::LINEAR;
        else
            return Filter::POINT;
    }

    switch (minFilter)
    {
    case SamplerFilter::LINEAR:
        return Filter::LINEAR;
    case SamplerFilter::LINEAR_MIPMAP_LINEAR:
        return Filter::LINEAR;
    case SamplerFilter::LINEAR_MIPMAP_NEAREST:
        return Filter::POINT;
    case SamplerFilter::NEAREST:
        return Filter::POINT;
    case SamplerFilter::NEAREST_MIPMAP_NEAREST:
        return Filter::POINT;
    case SamplerFilter::NEAREST_MIPMAP_LINEAR:
        return Filter::LINEAR;
    default:
        break;
    }

    return Filter::POINT;
}

cc::gfx::Address UtilsGFX::toAddressMode(SamplerAddressMode addressMode, bool isPow2)
{
    using cc::gfx::Address;
    Address ret = Address::WRAP;
    if (!isPow2 && (addressMode != SamplerAddressMode::CLAMP_TO_EDGE))
    {
        CCLOG(
            "Change texture wrap mode to CLAMP_TO_EDGE since non-power-of-two texture occur in %s %s %d",
            __FILE__,
            __FUNCTION__,
            __LINE__);
        return Address::CLAMP;
    }

    switch (addressMode)
    {
    case SamplerAddressMode::REPEAT:
        ret = Address::WRAP;
        break;
    case SamplerAddressMode::MIRROR_REPEAT:
        ret = Address::MIRROR;
        break;
    case SamplerAddressMode::CLAMP_TO_EDGE:
        ret = Address::CLAMP;
        break;
    default:
        break;
    }
    return ret;
}

void UtilsGFX::toTypes(PixelFormat textureFormat, cc::gfx::Format& format, bool& isCompressed)
{
    using cc::gfx::Format;
    format       = Format::UNKNOWN;
    isCompressed = false;
    switch (textureFormat)
    {
    case PixelFormat::RGBA8888:
        format = Format::RGBA8;
        break;
    case PixelFormat::RGB888:
        format = Format::RGB8;
        break;
    case PixelFormat::RGBA4444:
        format = Format::RGBA4;
        break;
    case PixelFormat::A8:
        // NOTE: use R8
        format = Format::R8;
        break;
    case PixelFormat::I8:
        format = Format::L8;
        // internalFormat = GL_LUMINANCE;
        // format = GL_LUMINANCE;
        // type = GL_UNSIGNED_BYTE;
        break;
    case PixelFormat::AI88:
        format = Format::LA8;
        // internalFormat = GL_LUMINANCE_ALPHA;
        // format = GL_LUMINANCE_ALPHA;
        // type = GL_UNSIGNED_BYTE;
        break;
    case PixelFormat::RGB565:
        format = Format::R5G6B5;
        break;
    case PixelFormat::RGB5A1:
        format = Format::RGB5A1;
        break;
    case PixelFormat::ETC1:
        format = Format::ETC_RGB8;
        // internalFormat = GL_ETC1_RGB8_OES;
        isCompressed = true;
        break;
    case PixelFormat::ETC2_RGB:
        format       = Format::ETC2_RGB8;
        isCompressed = true;
        break;
    case PixelFormat::ETC2_RGBA:
        format       = Format::ETC2_RGBA8;
        isCompressed = true;
        break;
    case PixelFormat::ATC_RGB:
        // internalFormat = GL_ATC_RGB_AMD;
        isCompressed = true;
        break;
    case PixelFormat::ATC_EXPLICIT_ALPHA:
        // internalFormat = GL_ATC_RGBA_EXPLICIT_ALPHA_AMD;
        isCompressed = true;
        break;
    case PixelFormat::ATC_INTERPOLATED_ALPHA:
        // internalFormat = GL_ATC_RGBA_INTERPOLATED_ALPHA_AMD;
        isCompressed = true;
        break;
    case PixelFormat::PVRTC2:
        format = Format::PVRTC_RGB2;
        // internalFormat = GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG;
        isCompressed = true;
        break;
    case PixelFormat::PVRTC2A:
        format = Format::PVRTC_RGBA2;
        // internalFormat = GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG;
        isCompressed = true;
        break;
    case PixelFormat::PVRTC4:
        format = Format::PVRTC_RGB4;
        // internalFormat = GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG;
        isCompressed = true;
        break;
    case PixelFormat::PVRTC4A:
        format = Format::PVRTC_RGBA4;
        // internalFormat = GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG;
        isCompressed = true;
        break;
    case PixelFormat::S3TC_DXT1:
        format = Format::BC1_ALPHA;
        // internalFormat = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
        isCompressed = true;
        break;
    case PixelFormat::S3TC_DXT3:
        format = Format::BC2;
        // internalFormat = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
        isCompressed = true;
        break;
    case PixelFormat::S3TC_DXT5:
        format = Format::BC3;
        // internalFormat = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
        isCompressed = true;
        break;
        // case PixelFormat::D16:
        //     format = GL_DEPTH_COMPONENT;
        //     internalFormat = GL_DEPTH_COMPONENT;
        //     type = GL_UNSIGNED_INT;
    case PixelFormat::D24S8:
        format = Format::DEPTH_STENCIL;
        break;
    default:
        break;
    }
}

cc::gfx::ComparisonFunc UtilsGFX::toComareFunction(CompareFunction compareFunction)
{
    using cc::gfx::ComparisonFunc;
    ComparisonFunc ret = ComparisonFunc::ALWAYS;
    switch (compareFunction)
    {
    case CompareFunction::NEVER:
        ret = ComparisonFunc::NEVER;
        break;
    case CompareFunction::LESS:
        ret = ComparisonFunc::LESS;
        break;
    case CompareFunction::LESS_EQUAL:
        ret = ComparisonFunc::LESS_EQUAL;
        break;
    case CompareFunction::GREATER:
        ret = ComparisonFunc::GREATER;
        break;
    case CompareFunction::GREATER_EQUAL:
        ret = ComparisonFunc::GREATER_EQUAL;
        break;
    case CompareFunction::NOT_EQUAL:
        ret = ComparisonFunc::NOT_EQUAL;
        break;
    case CompareFunction::EQUAL:
        ret = ComparisonFunc::EQUAL;
        break;
    case CompareFunction::ALWAYS:
        ret = ComparisonFunc::ALWAYS;
        break;
    default:
        break;
    }
    return ret;
}

cc::gfx::StencilOp UtilsGFX::toStencilOperation(StencilOperation stencilOperation)
{
    using cc::gfx::StencilOp;
    StencilOp ret = StencilOp::KEEP;
    switch (stencilOperation)
    {
    case StencilOperation::KEEP:
        ret = StencilOp::KEEP;
        break;
    case StencilOperation::ZERO:
        ret = StencilOp::ZERO;
        break;
    case StencilOperation::REPLACE:
        ret = StencilOp::REPLACE;
        break;
    case StencilOperation::INVERT:
        ret = StencilOp::INVERT;
        break;
    case StencilOperation::INCREMENT_WRAP:
        ret = StencilOp::INCR_WRAP;
        break;
    case StencilOperation::DECREMENT_WRAP:
        ret = StencilOp::DECR_WRAP;
        break;
    default:
        break;
    }
    return ret;
}

cc::gfx::BlendOp UtilsGFX::toBlendOperation(BlendOperation blendOperation)
{
    using cc::gfx::BlendOp;
    BlendOp ret = BlendOp::ADD;
    switch (blendOperation)
    {
    case BlendOperation::ADD:
        ret = BlendOp::ADD;
        break;
    case BlendOperation::SUBTRACT:
        ret = BlendOp::SUB;
        break;
    case BlendOperation::RESERVE_SUBTRACT:
        ret = BlendOp::REV_SUB;
        break;
    default:
        break;
    }
    return ret;
}

cc::gfx::BlendFactor UtilsGFX::toBlendFactor(BlendFactor blendFactor)
{
    cc::gfx::BlendFactor ret = cc::gfx::BlendFactor::ONE;
    switch (blendFactor)
    {
    case BlendFactor::ZERO:
        ret = cc::gfx::BlendFactor::ZERO;
        break;
    case BlendFactor::ONE:
        ret = cc::gfx::BlendFactor::ONE;
        break;
    case BlendFactor::SRC_COLOR:
        ret = cc::gfx::BlendFactor::SRC_COLOR;
        break;
    case BlendFactor::ONE_MINUS_SRC_COLOR:
        ret = cc::gfx::BlendFactor::ONE_MINUS_SRC_COLOR;
        break;
    case BlendFactor::SRC_ALPHA:
        ret = cc::gfx::BlendFactor::SRC_ALPHA;
        break;
    case BlendFactor::ONE_MINUS_SRC_ALPHA:
        ret = cc::gfx::BlendFactor::ONE_MINUS_SRC_ALPHA;
        break;
    case BlendFactor::DST_COLOR:
        ret = cc::gfx::BlendFactor::DST_COLOR;
        break;
    case BlendFactor::ONE_MINUS_DST_COLOR:
        ret = cc::gfx::BlendFactor::ONE_MINUS_DST_COLOR;
        break;
    case BlendFactor::DST_ALPHA:
        ret = cc::gfx::BlendFactor::DST_ALPHA;
        break;
    case BlendFactor::ONE_MINUS_DST_ALPHA:
        ret = cc::gfx::BlendFactor::ONE_MINUS_DST_ALPHA;
        break;
    case BlendFactor::SRC_ALPHA_SATURATE:
        ret = cc::gfx::BlendFactor::SRC_ALPHA_SATURATE;
        break;
    case BlendFactor::BLEND_CLOLOR:
        ret = cc::gfx::BlendFactor::CONSTANT_COLOR;
        break;
    case BlendFactor::CONSTANT_ALPHA:
        ret = cc::gfx::BlendFactor::CONSTANT_ALPHA;
        break;
    case BlendFactor::ONE_MINUS_CONSTANT_ALPHA:
        ret = cc::gfx::BlendFactor::ONE_MINUS_CONSTANT_ALPHA;
        break;
    default:
        break;
    }
    return ret;
}

cc::gfx::PrimitiveMode UtilsGFX::toPrimitiveType(PrimitiveType primitiveType)
{
    using cc::gfx::PrimitiveMode;
    PrimitiveMode ret = PrimitiveMode::TRIANGLE_LIST;
    switch (primitiveType)
    {
    case PrimitiveType::POINT:
        ret = PrimitiveMode::POINT_LIST;
        break;
    case PrimitiveType::LINE:
        ret = PrimitiveMode::LINE_LIST;
        break;
    case PrimitiveType::LINE_LOOP:
        ret = PrimitiveMode::LINE_LOOP;
        break;
    case PrimitiveType::LINE_STRIP:
        ret = PrimitiveMode::LINE_STRIP;
        break;
    case PrimitiveType::TRIANGLE:
        ret = PrimitiveMode::TRIANGLE_LIST;
        break;
    case PrimitiveType::TRIANGLE_STRIP:
        ret = PrimitiveMode::TRIANGLE_STRIP;
        break;
    default:
        break;
    }
    return ret;
}

cc::gfx::CullMode UtilsGFX::toCullMode(CullMode mode)
{
    switch (mode)
    {
    case CullMode::NONE:
        return cc::gfx::CullMode::NONE;
    case CullMode::BACK:
        return cc::gfx::CullMode::BACK;
    case CullMode::FRONT:
        return cc::gfx::CullMode::FRONT;
    default:;
    }
    return cc::gfx::CullMode::BACK;
}

cc::gfx::MemoryUsageBit UtilsGFX::toMemoryUsage(BufferUsage usage)
{
    switch (usage)
    {
    case BufferUsage::STATIC:
        return cc::gfx::MemoryUsageBit::DEVICE;  // GPU
    case BufferUsage::DYNAMIC:
        // return cc::gfx::MemoryUsageBit::HOST; // CPU
        return cc::gfx::MemoryUsageBit::DEVICE | cc::gfx::MemoryUsageBit::HOST;  // CPU+GPU
    default:;
    }
    return cc::gfx::MemoryUsageBit::DEVICE | cc::gfx::MemoryUsageBit::HOST;
}

cc::gfx::Format UtilsGFX::toFormat(cc::gfx::Type t)
{
    using cc::gfx::Format;
    switch (t)
    {
    case cc::gfx::Type::INT:
        return Format::R32I;
    case cc::gfx::Type::INT2:
        return Format::RG32I;
    case cc::gfx::Type::INT3:
        return Format::RGB32I;
    case cc::gfx::Type::INT4:
        return Format::RGBA32I;
    case cc::gfx::Type::UINT:
        return Format::R32UI;
    case cc::gfx::Type::UINT2:
        return Format::RG32UI;
    case cc::gfx::Type::UINT3:
        return Format::RGB32UI;
    case cc::gfx::Type::UINT4:
        return Format::RGBA32UI;
    case cc::gfx::Type::FLOAT:
        return Format::R32F;
    case cc::gfx::Type::FLOAT2:
        return Format::RG32F;
    case cc::gfx::Type::FLOAT3:
        return Format::RGB32F;
    case cc::gfx::Type::FLOAT4:
        return Format::RGBA32F;
    default:;
    }
    return Format::UNKNOWN;
}

cc::gfx::Texture* UtilsGFX::getTexture(TextureBackend* texture)
{
    if (!texture)
        return nullptr;
    switch (texture->getTextureType())
    {
    case TextureType::TEXTURE_2D:
        return static_cast<Texture2DGFX*>(texture)->getHandler();
    case TextureType::TEXTURE_CUBE:
        return static_cast<TextureCubeGFX*>(texture)->getHandler();
    case static_cast<TextureType>(3):
        return static_cast<TextureGFX*>(texture)->getHandler();
    default:;
    }
    return nullptr;
}

cc::gfx::Sampler* UtilsGFX::getSampler(TextureBackend* texture)
{
    if (!texture)
        return nullptr;
    switch (texture->getTextureType())
    {
    case TextureType::TEXTURE_2D:
        return static_cast<Texture2DGFX*>(texture)->getSampler();
    case TextureType::TEXTURE_CUBE:
        return static_cast<TextureCubeGFX*>(texture)->getSampler();
    case static_cast<TextureType>(3):
        return static_cast<TextureGFX*>(texture)->getSampler();
    default:;
    }
    return nullptr;
}

void UtilsGFX::glslangInitialize()
{
    static bool glslangInitialized = false;
    if (!glslangInitialized)
    {
        glslang::InitializeProcess();
        glslangInitialized = true;
    }
}

cc::gfx::Type UtilsGFX::toType(const glslang::TType* t)
{
    using cc::gfx::Type;
    if (!t)
        return Type::UNKNOWN;
    const auto btype = t->getBasicType();
    if (btype != glslang::EbtSampler)
    {
        const auto vsize = t->getVectorSize();
        if (t->isMatrix())
        {
            if (btype == glslang::EbtFloat)
            {
                const auto col = t->getMatrixCols();
                const auto row = t->getMatrixRows();
                if (2 <= col && col <= 4 && 2 <= row && row <= 4)
                {
                    return (Type)((int)Type::MAT2 + (col - 2) * 3 + row - 2);
                }
            }
        }
        else if (1 <= vsize && vsize <= 4)
        {
            switch (btype)
            {
            case glslang::EbtVoid:
                break;
            case glslang::EbtFloat:
                return (Type)((int)Type::FLOAT + vsize - 1);
            case glslang::EbtDouble:
                break;
            case glslang::EbtFloat16:
                break;
            case glslang::EbtInt8:
                break;
            case glslang::EbtUint8:
                break;
            case glslang::EbtInt16:
                break;
            case glslang::EbtUint16:
                break;
            case glslang::EbtInt:
                return (Type)((int)Type::INT + vsize - 1);
            case glslang::EbtUint:
                return (Type)((int)Type::UINT + vsize - 1);
            case glslang::EbtInt64:
                break;
            case glslang::EbtUint64:
                break;
            case glslang::EbtBool:
                return (Type)((int)Type::FLOAT + vsize - 1);
            case glslang::EbtAtomicUint:
                break;
            case glslang::EbtSampler:
                break;
            case glslang::EbtStruct:
                break;
            case glslang::EbtBlock:
                break;
            case glslang::EbtAccStruct:
                break;
            case glslang::EbtReference:
                break;
            case glslang::EbtRayQuery:
                break;
            case glslang::EbtString:
                break;
            case glslang::EbtNumTypes:
                break;
            default:;
            }
        }
    }
    else
    {
        // can be sampler/texture/image/subpass
        const auto& s = t->getSampler();
        if (s.isCombined())
        {
            switch (s.dim)
            {
            case glslang::EsdNone:
                break;
            case glslang::Esd1D:
                return s.isArrayed() ? Type::SAMPLER1D_ARRAY : Type::SAMPLER1D;
            case glslang::Esd2D:
                return s.isArrayed() ? Type::SAMPLER2D_ARRAY : Type::SAMPLER2D;
            case glslang::Esd3D:
                return Type::SAMPLER3D;
            case glslang::EsdCube:
                return Type::SAMPLER_CUBE;
            case glslang::EsdRect:
                break;
            case glslang::EsdBuffer:
                break;
            case glslang::EsdSubpass:
                break;
            case glslang::EsdNumDims:
                break;
            default:;
            }
        }
        else if (s.isTexture())
        {
            switch (s.dim)
            {
            case glslang::EsdNone:
                break;
            case glslang::Esd1D:
                return s.isArrayed() ? Type::TEXTURE1D_ARRAY : Type::TEXTURE1D;
            case glslang::Esd2D:
                return s.isArrayed() ? Type::TEXTURE2D_ARRAY : Type::TEXTURE2D;
            case glslang::Esd3D:
                return Type::TEXTURE3D;
            case glslang::EsdCube:
                return Type::TEXTURE_CUBE;
            case glslang::EsdRect:
                break;
            case glslang::EsdBuffer:
                break;
            case glslang::EsdSubpass:
                break;
            case glslang::EsdNumDims:
                break;
            default:;
            }
        }
        else if (s.isImage())
        {
            switch (s.dim)
            {
            case glslang::EsdNone:
                break;
            case glslang::Esd1D:
                return s.isArrayed() ? Type::IMAGE1D_ARRAY : Type::IMAGE1D;
            case glslang::Esd2D:
                return s.isArrayed() ? Type::IMAGE2D_ARRAY : Type::IMAGE2D;
            case glslang::Esd3D:
                return Type::IMAGE3D;
            case glslang::EsdCube:
                return Type::IMAGE_CUBE;
            case glslang::EsdRect:
                break;
            case glslang::EsdBuffer:
                break;
            case glslang::EsdSubpass:
                break;
            case glslang::EsdNumDims:
                break;
            default:;
            }
        }
    }
    return Type::UNKNOWN;
}

EShLanguage UtilsGFX::toGLSLangShaderStage(cc::gfx::ShaderStageFlagBit type)
{
    using cc::gfx::ShaderStageFlagBit;
    switch (type)
    {
    case ShaderStageFlagBit::VERTEX:
        return EShLangVertex;
    case ShaderStageFlagBit::CONTROL:
        return EShLangTessControl;
    case ShaderStageFlagBit::EVALUATION:
        return EShLangTessEvaluation;
    case ShaderStageFlagBit::GEOMETRY:
        return EShLangGeometry;
    case ShaderStageFlagBit::FRAGMENT:
        return EShLangFragment;
    case ShaderStageFlagBit::COMPUTE:
        return EShLangCompute;
    default:
    {
        CCASSERT(false, "Unsupported ShaderStageFlagBit, convert to EShLanguage failed.");
        return EShLangVertex;
    }
    }
}

glslang::EShTargetClientVersion UtilsGFX::toGLSLangClientVersion(int vkMinorVersion)
{
    switch (vkMinorVersion)
    {
    case 0:
        return glslang::EShTargetVulkan_1_0;
    case 1:
        return glslang::EShTargetVulkan_1_1;
    case 2:
        return glslang::EShTargetVulkan_1_2;
    default:
    {
        CCASSERT(false, "Unsupported vulkan version, convert to EShTargetClientVersion failed.");
        return glslang::EShTargetVulkan_1_0;
    }
    }
}

glslang::EShTargetLanguageVersion UtilsGFX::toGLSLangTargetVersion(int vkMinorVersion)
{
    switch (vkMinorVersion)
    {
    case 0:
        return glslang::EShTargetSpv_1_0;
    case 1:
        return glslang::EShTargetSpv_1_3;
    case 2:
        return glslang::EShTargetSpv_1_5;
    default:
    {
        CCASSERT(false, "Unsupported vulkan version, convert to EShTargetLanguageVersion failed.");
        return glslang::EShTargetSpv_1_0;
    }
    }
}

std::vector<uint32_t> UtilsGFX::compileGLSLtoSPIRV(
    cc::gfx::ShaderStageFlagBit stage, const std::string& source, int vkMinorVersion)
{
    glslangInitialize();
    auto envStage = toGLSLangShaderStage(stage);
    if (vkMinorVersion < 0 || vkMinorVersion > 2)
    {
        log("%s: invalid minor version", __FUNCTION__);
        return {};
    }

    const int clientInputSemanticsVersion = 100 + vkMinorVersion * 10;
    const bool isForwardCompatible        = false;
    EShMessages controls                  = (EShMessages)(EShMsgSpvRules | EShMsgVulkanRules);
    glslang::TShader shader(envStage);
    const char* vstring = source.c_str();
    const int vlength   = source.size();
    shader.setStringsWithLengths(&vstring, &vlength, 1);
    // -> #define VULKAN 1X0
    shader.setEnvInput(glslang::EShSourceGlsl, envStage, glslang::EShClientVulkan, clientInputSemanticsVersion);
    //-> Vulkan 1.X
    shader.setEnvClient(glslang::EShClientVulkan, toGLSLangClientVersion(vkMinorVersion));
    // -> SPIR-V 1.Y
    shader.setEnvTarget(glslang::EshTargetSpv, toGLSLangTargetVersion(vkMinorVersion));
    bool success = shader.parse(&DefaultTBuiltInResource, clientInputSemanticsVersion, isForwardCompatible, controls);
    if (!success)
    {
        log("GLSL Parsing Failed:\n%s\n%s", shader.getInfoLog(), shader.getInfoDebugLog());
        return {};
    }

    glslang::TProgram program;
    program.addShader(&shader);

    if (!program.link(controls))
    {
        log("GLSL Linking Failed:\n%s\n%s", program.getInfoLog(), program.getInfoDebugLog());
        return {};
    }

    if (!program.buildReflection())
    {
        log("GLSL Reflection Failed");
        return {};
    }
    program.dumpReflection();
    auto num = program.getNumUniformBlocks();
    for (int i = 0; i < num; ++i)
    {
        auto info = program.getUniformBlock(i);
        info.dump();
    }

    spv::SpvBuildLogger logger;
    glslang::SpvOptions spvOptions;
    std::vector<uint32_t> spirv;
    glslang::GlslangToSpv(*program.getIntermediate(envStage), spirv, &logger, &spvOptions);
    if (spirv.empty())
    {
        log("GlslangToSpv Failed:\n%s\n%s", program.getInfoLog(), program.getInfoDebugLog());
        return {};
    }
    return spirv;
}

std::string UtilsGFX::compileSPIRVtoGLSL(const std::vector<uint32_t>& spirv, uint32_t version, bool isES)
{
    glslangInitialize();
    if (spirv.empty())
        return {};
    spirv_cross::CompilerGLSL glsl(spirv);
    spirv_cross::CompilerGLSL::Options options;
    options.version = version;
    options.es      = isES;
    // options.force_flattened_io_blocks = true;
    glsl.set_common_options(options);

    const auto resources = glsl.get_shader_resources();
    for (const auto& u : resources.uniform_buffers)
    {
        // use '_BlockName' as instance name
        glsl.set_name(u.id, "_" + u.name);
    }

    return glsl.compile();
}

const TBuiltInResource UtilsGFX::DefaultTBuiltInResource = {
    /* .MaxLights = */ 32,
    /* .MaxClipPlanes = */ 6,
    /* .MaxTextureUnits = */ 32,
    /* .MaxTextureCoords = */ 32,
    /* .MaxVertexAttribs = */ 64,
    /* .MaxVertexUniformComponents = */ 4096,
    /* .MaxVaryingFloats = */ 64,
    /* .MaxVertexTextureImageUnits = */ 32,
    /* .MaxCombinedTextureImageUnits = */ 80,
    /* .MaxTextureImageUnits = */ 32,
    /* .MaxFragmentUniformComponents = */ 4096,
    /* .MaxDrawBuffers = */ 32,
    /* .MaxVertexUniformVectors = */ 128,
    /* .MaxVaryingVectors = */ 8,
    /* .MaxFragmentUniformVectors = */ 16,
    /* .MaxVertexOutputVectors = */ 16,
    /* .MaxFragmentInputVectors = */ 15,
    /* .MinProgramTexelOffset = */ -8,
    /* .MaxProgramTexelOffset = */ 7,
    /* .MaxClipDistances = */ 8,
    /* .MaxComputeWorkGroupCountX = */ 65535,
    /* .MaxComputeWorkGroupCountY = */ 65535,
    /* .MaxComputeWorkGroupCountZ = */ 65535,
    /* .MaxComputeWorkGroupSizeX = */ 1024,
    /* .MaxComputeWorkGroupSizeY = */ 1024,
    /* .MaxComputeWorkGroupSizeZ = */ 64,
    /* .MaxComputeUniformComponents = */ 1024,
    /* .MaxComputeTextureImageUnits = */ 16,
    /* .MaxComputeImageUniforms = */ 8,
    /* .MaxComputeAtomicCounters = */ 8,
    /* .MaxComputeAtomicCounterBuffers = */ 1,
    /* .MaxVaryingComponents = */ 60,
    /* .MaxVertexOutputComponents = */ 64,
    /* .MaxGeometryInputComponents = */ 64,
    /* .MaxGeometryOutputComponents = */ 128,
    /* .MaxFragmentInputComponents = */ 128,
    /* .MaxImageUnits = */ 8,
    /* .MaxCombinedImageUnitsAndFragmentOutputs = */ 8,
    /* .MaxCombinedShaderOutputResources = */ 8,
    /* .MaxImageSamples = */ 0,
    /* .MaxVertexImageUniforms = */ 0,
    /* .MaxTessControlImageUniforms = */ 0,
    /* .MaxTessEvaluationImageUniforms = */ 0,
    /* .MaxGeometryImageUniforms = */ 0,
    /* .MaxFragmentImageUniforms = */ 8,
    /* .MaxCombinedImageUniforms = */ 8,
    /* .MaxGeometryTextureImageUnits = */ 16,
    /* .MaxGeometryOutputVertices = */ 256,
    /* .MaxGeometryTotalOutputComponents = */ 1024,
    /* .MaxGeometryUniformComponents = */ 1024,
    /* .MaxGeometryVaryingComponents = */ 64,
    /* .MaxTessControlInputComponents = */ 128,
    /* .MaxTessControlOutputComponents = */ 128,
    /* .MaxTessControlTextureImageUnits = */ 16,
    /* .MaxTessControlUniformComponents = */ 1024,
    /* .MaxTessControlTotalOutputComponents = */ 4096,
    /* .MaxTessEvaluationInputComponents = */ 128,
    /* .MaxTessEvaluationOutputComponents = */ 128,
    /* .MaxTessEvaluationTextureImageUnits = */ 16,
    /* .MaxTessEvaluationUniformComponents = */ 1024,
    /* .MaxTessPatchComponents = */ 120,
    /* .MaxPatchVertices = */ 32,
    /* .MaxTessGenLevel = */ 64,
    /* .MaxViewports = */ 16,
    /* .MaxVertexAtomicCounters = */ 0,
    /* .MaxTessControlAtomicCounters = */ 0,
    /* .MaxTessEvaluationAtomicCounters = */ 0,
    /* .MaxGeometryAtomicCounters = */ 0,
    /* .MaxFragmentAtomicCounters = */ 8,
    /* .MaxCombinedAtomicCounters = */ 8,
    /* .MaxAtomicCounterBindings = */ 1,
    /* .MaxVertexAtomicCounterBuffers = */ 0,
    /* .MaxTessControlAtomicCounterBuffers = */ 0,
    /* .MaxTessEvaluationAtomicCounterBuffers = */ 0,
    /* .MaxGeometryAtomicCounterBuffers = */ 0,
    /* .MaxFragmentAtomicCounterBuffers = */ 1,
    /* .MaxCombinedAtomicCounterBuffers = */ 1,
    /* .MaxAtomicCounterBufferSize = */ 16384,
    /* .MaxTransformFeedbackBuffers = */ 4,
    /* .MaxTransformFeedbackInterleavedComponents = */ 64,
    /* .MaxCullDistances = */ 8,
    /* .MaxCombinedClipAndCullDistances = */ 8,
    /* .MaxSamples = */ 4,
    /* .maxMeshOutputVerticesNV = */ 256,
    /* .maxMeshOutputPrimitivesNV = */ 512,
    /* .maxMeshWorkGroupSizeX_NV = */ 32,
    /* .maxMeshWorkGroupSizeY_NV = */ 1,
    /* .maxMeshWorkGroupSizeZ_NV = */ 1,
    /* .maxTaskWorkGroupSizeX_NV = */ 32,
    /* .maxTaskWorkGroupSizeY_NV = */ 1,
    /* .maxTaskWorkGroupSizeZ_NV = */ 1,
    /* .maxMeshViewCountNV = */ 4,
    /* .maxDualSourceDrawBuffersEXT = */ 1,

    /* .limits = */
    {
        /* .nonInductiveForLoops = */ 1,
        /* .whileLoops = */ 1,
        /* .doWhileLoops = */ 1,
        /* .generalUniformIndexing = */ 1,
        /* .generalAttributeMatrixVectorIndexing = */ 1,
        /* .generalVaryingIndexing = */ 1,
        /* .generalSamplerIndexing = */ 1,
        /* .generalVariableIndexing = */ 1,
        /* .generalConstantMatrixVectorIndexing = */ 1,
    }};

CC_BACKEND_END
