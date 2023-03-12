#pragma once
#include "renderer/backend/DeviceInfo.h"

CC_BACKEND_BEGIN

class DeviceInfoGFX : public DeviceInfo
{
public:
    DeviceInfoGFX()          = default;
    ~DeviceInfoGFX() override = default;

    /**
     * Gather features and implementation limits
     */
    bool init() override;

    /**
     * Get vendor device name.
     * @return Vendor device name.
     */
    const char* getVendor() const override;

    /**
     * Get the full name of the vendor device.
     * @return The full name of the vendor device.
     */
    const char* getRenderer() const override;

    /**
     * Get version name.
     * @return Version name.
     */
    const char* getVersion() const override;

    /**
     * get OpenGFX ES extensions.
     * @return Extension supported by OpenGFX ES.
     */
    const char* getExtension() const override;

    /**
     * Check if feature supported by OpenGFX ES.
     * @param feature Specify feature to be query.
     * @return true if the feature is supported, false otherwise.
     */
    bool checkForFeatureSupported(FeatureType feature) override;

private:
    std::string _deviceName;
    std::string _rendererName;
    std::string _vendor;
};

CC_BACKEND_END
