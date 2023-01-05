#include "DeviceInfoGFX.h"
#include "gfx/backend/GFXDeviceManager.h"

CC_BACKEND_BEGIN

bool DeviceInfoGFX::init()
{
	const auto device = cc::gfx::Device::getInstance();
	const auto& cap = device->getCapabilities();
    _maxAttributes = cap.maxVertexAttributes;
    _maxTextureSize = cap.maxTextureSize;
    _maxTextureUnits = cap.maxTextureUnits;
    _deviceName = device->getDeviceName();
    _rendererName = device->getRenderer();
    _vendor = device->getVendor();
    return true;
}

const char* DeviceInfoGFX::getVendor() const
{
    return _vendor.c_str();
}
const char* DeviceInfoGFX::getRenderer() const
{
    return _rendererName.c_str();
}

const char* DeviceInfoGFX::getVersion() const
{
    return _deviceName.c_str();
}

const char* DeviceInfoGFX::getExtension() const
{
    return "";
}

bool DeviceInfoGFX::checkForFeatureSupported(FeatureType feature)
{
    using cc::gfx::Feature;
    const auto device = cc::gfx::Device::getInstance();
    bool featureSupported = false;
    switch (feature)
    {
    case FeatureType::ETC1:
        //featureSupported = device->hasFeature(Feature::FORMAT_ETC1);
        featureSupported = true;
        break;
    case FeatureType::S3TC:
        //cc::gfx::Format::BC1_ALPHA;
        featureSupported = true;
        break;
    case FeatureType::AMD_COMPRESSED_ATC:
        featureSupported = false;
        break;
    case FeatureType::PVRTC:
        //featureSupported = device->hasFeature(Feature::FORMAT_PVRTC);
        featureSupported = true;
        break;
    case FeatureType::IMG_FORMAT_BGRA8888:
        featureSupported = true;
        break;
    case FeatureType::DISCARD_FRAMEBUFFER:
        featureSupported = false;
        break;
    case FeatureType::PACKED_DEPTH_STENCIL:
        //featureSupported = device->hasFeature(Feature::FORMAT_D24S8);
        featureSupported = true;
        break;
    case FeatureType::VAO:
        featureSupported = true;
        break;
    case FeatureType::MAPBUFFER:
        featureSupported = true;
        break;
    case FeatureType::DEPTH24:
        //featureSupported = device->hasFeature(Feature::FORMAT_D24);
        featureSupported = false;
        break;
    default:
        break;
    }
    return featureSupported;
}

CC_BACKEND_END
