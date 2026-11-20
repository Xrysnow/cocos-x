#pragma once

#include "platform/PlatformDefine.h"

#include <cstddef>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

namespace cc
{

enum class TextInputIndexError { none, invalidUtf8, outOfRange, notBoundary };

struct TextInputIndexResult
{
    std::size_t offset = 0;
    TextInputIndexError error = TextInputIndexError::none;
    explicit operator bool() const { return error == TextInputIndexError::none; }
};

// Store this index alongside a validated snapshot if multiple queries use its text.
class CC_DLL TextInputIndex
{
public:
    explicit TextInputIndex(std::string_view utf8);
    bool valid() const { return !_boundaries.empty(); }

    TextInputIndexResult scalarCount() const;
    TextInputIndexResult utf8FromScalar(std::size_t scalar) const;
    TextInputIndexResult utf16FromScalar(std::size_t scalar) const;
    TextInputIndexResult scalarFromUtf8(std::size_t byte) const;
    TextInputIndexResult scalarFromUtf16(std::size_t codeUnit) const;

    static std::optional<std::string> encode(char32_t scalar);

private:
    struct Boundary
    {
        std::size_t utf8;
        std::size_t utf16;
    };

    TextInputIndexResult scalarFrom(std::size_t offset, std::size_t Boundary::*member) const;

    std::vector<Boundary> _boundaries;
};

}  // namespace cc
