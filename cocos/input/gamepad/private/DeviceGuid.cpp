#include "DeviceGuid.h"

#include <algorithm>
#include <charconv>

namespace cc::input::detail
{
namespace
{

constexpr std::string_view hexDigits = "0123456789abcdef";

void write16(DeviceGuid& guid, unsigned offset, std::uint16_t value)
{
    guid.bytes[offset] = static_cast<std::uint8_t>(value);
    guid.bytes[offset + 1] = static_cast<std::uint8_t>(value >> 8);
}

std::uint16_t read16(const DeviceGuid& guid, unsigned offset)
{
    return static_cast<std::uint16_t>(guid.bytes[offset] | (guid.bytes[offset + 1] << 8));
}

bool hasBus(const DeviceGuid& guid)
{
    const auto bus = read16(guid, 0);
    return bus < 32 || bus == 0xff;
}

bool hasProductIds(const DeviceGuid& guid)
{
    return hasBus(guid) && read16(guid, 6) == 0 && read16(guid, 10) == 0;
}

} // namespace

std::uint16_t DeviceGuid::nameChecksum(std::uint16_t crc, std::string_view text) noexcept
{
    for (const unsigned char byte : text)
    {
        crc ^= byte;
        for (unsigned bit = 0; bit < 8; ++bit)
            crc = static_cast<std::uint16_t>((crc >> 1) ^ ((crc & 1) ? 0xa001 : 0));
    }
    return crc;
}

std::optional<DeviceGuid> DeviceGuid::parse(std::string_view hex)
{
    DeviceGuid guid;
    if (hex.size() != guid.bytes.size() * 2)
        return {};
    for (std::size_t i = 0; i < guid.bytes.size(); ++i)
    {
        const char* start = hex.data() + i * 2;
        unsigned byte = 0;
        const auto result = std::from_chars(start, start + 2, byte, 16);
        if (result.ec != std::errc{} || result.ptr != start + 2)
            return {};
        guid.bytes[i] = static_cast<std::uint8_t>(byte);
    }
    return guid;
}

DeviceGuid DeviceGuid::make(std::uint16_t bus, std::uint16_t vendor, std::uint16_t product,
                            std::uint16_t version, std::string_view manufacturer,
                            std::string_view name, std::uint8_t signature,
                            std::uint8_t driverData)
{
    DeviceGuid guid;
    std::uint16_t crc = 0;
    if (!manufacturer.empty() && !name.empty())
        crc = nameChecksum(nameChecksum(crc, manufacturer), " ");
    write16(guid, 0, bus);
    write16(guid, 2, nameChecksum(crc, name));
    if (vendor)
    {
        write16(guid, 4, vendor);
        write16(guid, 8, product);
        write16(guid, 12, version);
    }
    else
    {
        const std::size_t maxNameLength = signature ? 9 : 11;
        std::copy_n(name.begin(), std::min(maxNameLength, name.size()), guid.bytes.begin() + 4);
    }
    if (vendor || signature)
    {
        guid.bytes[14] = signature;
        guid.bytes[15] = driverData;
    }
    return guid;
}

std::string DeviceGuid::str() const
{
    std::string result;
    result.reserve(32);
    for (auto byte : bytes)
    {
        result.push_back(hexDigits[byte >> 4]);
        result.push_back(hexDigits[byte & 15]);
    }
    return result;
}

DeviceGuid DeviceGuid::android(std::uint16_t vendor, std::uint16_t product, std::string_view descriptor,
                              std::uint16_t buttons, std::uint16_t axes)
{
    auto guid = make(5, vendor, product, 0, {}, descriptor);
    // Android reserves these bytes for its input capability masks, including on name-only devices.
    write16(guid, 12, buttons);
    write16(guid, 14, axes);
    return guid;
}

std::uint16_t DeviceGuid::crc() const noexcept { return hasBus(*this) ? read16(*this, 2) : 0; }
std::uint16_t DeviceGuid::vendor() const noexcept { return hasProductIds(*this) ? read16(*this, 4) : 0; }
std::uint16_t DeviceGuid::product() const noexcept { return hasProductIds(*this) ? read16(*this, 8) : 0; }

bool DeviceGuid::usesVersion() const noexcept
{
    return bytes[14] != 'm' && vendor() != 0 && product() != 0;
}

DeviceGuid DeviceGuid::withoutCrc() const noexcept
{
    auto result = *this;
    if (hasBus(*this))
        write16(result, 2, 0);
    return result;
}

DeviceGuid DeviceGuid::withoutVersion() const noexcept
{
    auto result = *this;
    if (usesVersion())
        write16(result, 12, 0);
    return result;
}

DeviceGuid DeviceGuid::migrateLegacy(std::string_view platform) const noexcept
{
    constexpr std::array<std::uint8_t, 6> signature{'P', 'I', 'D', 'V', 'I', 'D'};
    const auto isZero = [](std::uint8_t value) { return value == 0; };
    const bool oldWindows = platform == "Windows" &&
        std::equal(signature.begin(), signature.end(), bytes.begin() + 10);
    const bool oldMac = platform == "macOS" &&
        std::all_of(bytes.begin() + 2, bytes.begin() + 8, isZero) &&
        std::all_of(bytes.begin() + 10, bytes.end(), isZero);
    if (!oldWindows && !oldMac)
        return *this;

    DeviceGuid migrated;
    write16(migrated, 0, 3);
    write16(migrated, 4, read16(*this, 0));
    write16(migrated, 8, read16(*this, oldWindows ? 2 : 8));
    return migrated;
}

} // namespace cc::input::detail
