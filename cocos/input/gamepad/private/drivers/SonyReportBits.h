#pragma once

#include <bit>
#include <cstdint>
#include <span>

namespace cc::input::detail::playstation {

inline std::uint32_t crc(std::uint8_t seed, std::span<const std::uint8_t> packet)
{
    std::uint32_t value = 0xffffffffu ^ seed;
    const auto octet = [&] {
        for (unsigned bit = 0; bit < 8; ++bit)
            value = (value >> 1) ^ ((value & 1u) ? 0xedb88320u : 0u);
    };
    octet();
    for (auto byte : packet)
    {
        value ^= byte;
        octet();
    }
    return ~value;
}

inline std::uint32_t little(std::span<const std::uint8_t> bytes)
{
    std::uint32_t value = 0;
    for (unsigned i = 0; i < bytes.size(); ++i)
        value |= static_cast<std::uint32_t>(bytes[i]) << (i * 8);
    return value;
}

inline void store(std::span<std::uint8_t> bytes, std::uint32_t value)
{
    for (auto& byte : bytes)
    {
        byte = static_cast<std::uint8_t>(value);
        value >>= 8;
    }
}

inline int signedSample(std::span<const std::uint8_t> bytes, unsigned offset)
{
    return std::bit_cast<std::int16_t>(static_cast<std::uint16_t>(little(bytes.subspan(offset, 2))));
}

} // namespace cc::input::detail::playstation
