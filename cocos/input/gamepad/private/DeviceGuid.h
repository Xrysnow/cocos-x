#pragma once

#include <array>
#include <compare>
#include <cstdint>
#include <optional>
#include <string>
#include <string_view>

namespace cc::input::detail
{

struct DeviceGuid
{
    std::array<std::uint8_t, 16> bytes{};

    static std::optional<DeviceGuid> parse(std::string_view hex);
    static std::uint16_t nameChecksum(std::uint16_t seed, std::string_view text) noexcept;
    static DeviceGuid make(std::uint16_t bus, std::uint16_t vendor, std::uint16_t product,
                           std::uint16_t version, std::string_view manufacturer,
                           std::string_view name, std::uint8_t signature = 0,
                           std::uint8_t driverData = 0);
    static DeviceGuid android(std::uint16_t vendor, std::uint16_t product, std::string_view descriptor,
                              std::uint16_t buttons, std::uint16_t axes);

    std::string str() const;
    std::uint16_t crc() const noexcept;
    std::uint16_t vendor() const noexcept;
    std::uint16_t product() const noexcept;
    bool usesVersion() const noexcept;
    DeviceGuid withoutCrc() const noexcept;
    DeviceGuid withoutVersion() const noexcept;
    DeviceGuid migrateLegacy(std::string_view platform) const noexcept;
    auto operator<=>(const DeviceGuid&) const = default;
};

} // namespace cc::input::detail
