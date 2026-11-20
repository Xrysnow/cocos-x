#include "platform/TextInputIndex.h"

#include "base/ccUTF8.h"

#include <algorithm>

namespace cc
{

TextInputIndex::TextInputIndex(std::string_view utf8)
{
    std::u32string scalars;
    if (!StringUtils::UTF8ToUTF32(utf8, scalars))
        return;

    Boundary boundary{0, 0};
    _boundaries.reserve(scalars.size() + 1);
    _boundaries.push_back(boundary);
    for (const auto scalar : scalars)
    {
        boundary.utf8 += scalar < 0x80 ? 1 : scalar < 0x800 ? 2 : scalar < 0x10000 ? 3 : 4;
        boundary.utf16 += scalar < 0x10000 ? 1 : 2;
        _boundaries.push_back(boundary);
    }
}

TextInputIndexResult TextInputIndex::scalarCount() const
{
    if (!valid())
        return {0, TextInputIndexError::invalidUtf8};
    return {_boundaries.size() - 1};
}

TextInputIndexResult TextInputIndex::utf8FromScalar(std::size_t scalar) const
{
    if (!valid())
        return {0, TextInputIndexError::invalidUtf8};
    if (scalar >= _boundaries.size())
        return {0, TextInputIndexError::outOfRange};
    return {_boundaries[scalar].utf8};
}

TextInputIndexResult TextInputIndex::utf16FromScalar(std::size_t scalar) const
{
    if (!valid())
        return {0, TextInputIndexError::invalidUtf8};
    if (scalar >= _boundaries.size())
        return {0, TextInputIndexError::outOfRange};
    return {_boundaries[scalar].utf16};
}

TextInputIndexResult TextInputIndex::scalarFromUtf8(std::size_t byte) const
{
    return scalarFrom(byte, &Boundary::utf8);
}

TextInputIndexResult TextInputIndex::scalarFromUtf16(std::size_t codeUnit) const
{
    return scalarFrom(codeUnit, &Boundary::utf16);
}

TextInputIndexResult TextInputIndex::scalarFrom(std::size_t offset, std::size_t Boundary::*member) const
{
    if (!valid())
        return {0, TextInputIndexError::invalidUtf8};
    if (offset > _boundaries.back().*member)
        return {0, TextInputIndexError::outOfRange};

    const auto match = std::lower_bound(_boundaries.begin(), _boundaries.end(), offset,
                                        [member](Boundary boundary, std::size_t value) { return boundary.*member < value; });
    if ((*match).*member != offset)
        return {0, TextInputIndexError::notBoundary};
    return {static_cast<std::size_t>(match - _boundaries.begin())};
}

std::optional<std::string> TextInputIndex::encode(char32_t scalar)
{
    if (scalar > 0x10FFFF || (scalar >= 0xD800 && scalar <= 0xDFFF))
        return std::nullopt;

    std::string utf8;
    if (!StringUtils::UTF32ToUTF8(std::u32string_view(&scalar, 1), utf8))
        return std::nullopt;
    return utf8;
}

}  // namespace cc
