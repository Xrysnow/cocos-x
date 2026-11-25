#pragma once

#include <cerrno>
#include <charconv>
#include <filesystem>
#include <fstream>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

namespace cc::system_info::linux_detail
{
inline std::string_view trim(std::string_view text)
{
    constexpr auto whitespace = " \t\n\r";
    auto first = text.find_first_not_of(whitespace);
    if (first == std::string_view::npos)
        return {};
    return text.substr(first, text.find_last_not_of(whitespace) - first + 1);
}

inline std::optional<std::string> readText(const std::filesystem::path& path, int* error = nullptr)
{
    errno = 0;
    std::ifstream file(path);
    if (!file)
    {
        if (error)
            *error = errno ? errno : EIO;
        return std::nullopt;
    }
    if (error)
        *error = 0;
    std::string text;
    for (std::string line; std::getline(file, line);)
    {
        text += line;
        text += '\n';
    }
    if (file.bad())
    {
        if (error)
            *error = errno ? errno : EIO;
        return std::nullopt;
    }
    return std::string(trim(text));
}

template <typename T>
std::optional<T> number(std::string_view text)
{
    text = trim(text);
    if (text.empty())
        return std::nullopt;
    T value{};
    auto end = text.data() + text.size();
    auto result = std::from_chars(text.data(), end, value);
    if (result.ec != std::errc{} || result.ptr != end)
        return std::nullopt;
    return value;
}

template <typename T>
std::optional<T> readNumber(const std::filesystem::path& path, int* error = nullptr)
{
    auto text = readText(path, error);
    return text ? number<T>(*text) : std::nullopt;
}

inline std::vector<std::string_view> words(std::string_view line, std::string_view separators = " \t")
{
    std::vector<std::string_view> result;
    auto first = line.find_first_not_of(separators);
    while (first != std::string_view::npos)
    {
        auto end = line.find_first_of(separators, first);
        result.push_back(line.substr(first, end == std::string_view::npos ? end : end - first));
        first = line.find_first_not_of(separators, end);
    }
    return result;
}

inline std::vector<unsigned int> cpuList(std::string_view text)
{
    std::vector<unsigned int> result;
    for (auto range : words(text, ","))
    {
        auto delimiter = range.find('-');
        auto first = number<unsigned int>(range.substr(0, delimiter));
        auto last = delimiter == std::string_view::npos ? first : number<unsigned int>(range.substr(delimiter + 1));
        // The kernel's CPU masks are much smaller than this, including on large servers.
        if (!first || !last || *first > *last || *last >= 1'000'000)
            return {};
        for (auto cpu = *first; cpu <= *last; ++cpu)
            result.push_back(cpu);
    }
    return result;
}
} // namespace cc::system_info::linux_detail
