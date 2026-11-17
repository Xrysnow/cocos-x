#pragma once

#include <functional>
#include <string>
#include <string_view>

namespace hlookup {
struct string_hash
{
    using hash_type      = std::hash<std::string_view>;
    using is_transparent = void;

    size_t operator()(const char* str) const { return hash_type{}(str); }
    size_t operator()(std::string_view str) const { return hash_type{}(str); }
    size_t operator()(const std::string& str) const { return hash_type{}(str); }
};

struct equal_to
{
    template <class _Ty1, class _Ty2>
    constexpr auto operator()(_Ty1&& _Left, _Ty2&& _Right) const
        noexcept(noexcept(static_cast<_Ty1&&>(_Left) == static_cast<_Ty2&&>(_Right)))  // strengthened
        -> decltype(static_cast<_Ty1&&>(_Left) == static_cast<_Ty2&&>(_Right))
    {
        return static_cast<_Ty1&&>(_Left) == static_cast<_Ty2&&>(_Right);
    }

    using is_transparent = void;
};

} // namespace hlookup
