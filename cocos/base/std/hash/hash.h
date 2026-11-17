#pragma once
#include <cstddef>
#include <cstdint>
#include <string>
#include "xxhash/xxhash.h"

namespace ccstd
{
    using hash_t = std::uint32_t;

    template <typename T>
    void hash_combine(uint64_t& seed, T value)
    {
        seed = XXH64(&value, sizeof(T), seed);
    }

    inline void hash_combine(uint64_t& seed, const std::string& value)
    {
        seed = XXH64(value.c_str(), value.size(), seed);
    }

    inline void hash_combine(uint64_t& seed, bool value)
    {
        const uint32_t v = value ? 1 : 0;
        seed = XXH64(&v, sizeof(v), seed);
    }

    template <typename T>
    void hash_combine(uint32_t& seed, T value)
    {
        seed = XXH32(&value, sizeof(T), seed);
    }

    inline void hash_combine(uint32_t& seed, const std::string& value)
    {
        seed = XXH32(value.c_str(), value.size(), seed);
    }

    inline void hash_combine(uint32_t& seed, bool value)
    {
        const uint32_t v = value ? 1 : 0;
        seed = XXH32(&v, sizeof(v), seed);
    }

    inline hash_t hash_range(const void* start, const void* end)
    {
        const auto diff = (const char*)end - (const char*)start;
        if constexpr (sizeof(hash_t) == sizeof(uint64_t))
        {
            return XXH64(start, diff, 0);
        }
        else
        {
            return XXH32(start, diff, 0);
        }
    }

    inline hash_t hash_value(const void* value)
    {
        if constexpr (sizeof(hash_t) == sizeof(uint64_t))
        {
            return XXH64(&value, sizeof(void*), 0);
        }
        else
        {
            return XXH32(&value, sizeof(void*), 0);
        }
    }
}
