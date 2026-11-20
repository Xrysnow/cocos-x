#pragma once

#include "platform/TextInputIndex.h"
#include "platform/TextInputTypes.h"

#include <algorithm>
#include <limits>
#include <optional>
#include <string_view>

namespace cc::wayland_text_input
{

// Version 1 keeps the number of commit requests on each text-input object.
// Check the serial against the whole current activation, including wrapped serials.
inline bool inActivation(std::uint32_t serial, std::uint32_t first, std::uint32_t last)
{
    return (serial - first) <= (last - first);
}

struct Surrounding
{
    std::string text;
    std::size_t origin;
    std::size_t anchor;
    std::size_t focus;
    std::int32_t cursorByte;
    std::int32_t anchorByte;
};

inline std::optional<Surrounding> surrounding(const TextInputSnapshot& snapshot)
{
    constexpr std::size_t maxBytes = 4000;
    const auto& text = snapshot.utf8;
    if (snapshot.focus < snapshot.origin || snapshot.anchor < snapshot.origin)
        return std::nullopt;

    const TextInputIndex index(text);
    const auto cursor = index.utf8FromScalar(snapshot.focus - snapshot.origin);
    const auto anchor = index.utf8FromScalar(snapshot.anchor - snapshot.origin);
    if (!cursor || !anchor)
        return std::nullopt;

    const auto low = std::min(cursor.offset, anchor.offset);
    const auto high = std::max(cursor.offset, anchor.offset);
    const auto selected = high - low;
    if (selected > maxBytes)
        return std::nullopt;

    const auto extraBefore = (maxBytes - selected) / 2;
    auto begin = low - std::min(low, extraBefore);
    if (text.size() > maxBytes)
        begin = std::min(begin, text.size() - maxBytes);
    else
        begin = 0;
    const auto continuation = [&](std::size_t byte) {
        return byte < text.size() && (static_cast<unsigned char>(text[byte]) & 0xC0) == 0x80;
    };
    while (continuation(begin))
        ++begin;
    auto end = begin + std::min(maxBytes, text.size() - begin);
    while (continuation(end))
        --end;
    const auto clip = std::string_view(text).substr(begin, end - begin);
    const auto clipOrigin = index.scalarFromUtf8(begin);
    if (!clipOrigin || clipOrigin.offset > (std::numeric_limits<std::size_t>::max)() - snapshot.origin ||
        begin > low || end < high || clip.find('\0') != std::string_view::npos)
        return std::nullopt;

    return Surrounding{std::string(clip), snapshot.origin + clipOrigin.offset, snapshot.anchor, snapshot.focus,
                       static_cast<std::int32_t>(cursor.offset - begin),
                       static_cast<std::int32_t>(anchor.offset - begin)};
}

struct EditPlan
{
    TextInputEdit edit;
    TextInputSnapshot predicted;
};

inline std::optional<EditPlan> planEdit(const TextInputSnapshot& snapshot,
                                        const Surrounding* published,
                                        std::uint32_t before,
                                        std::uint32_t after,
                                        std::string_view commit,
                                        std::uint64_t transactionId)
{
    if (snapshot.anchor < snapshot.origin || snapshot.focus < snapshot.origin ||
        snapshot.revision == (std::numeric_limits<std::uint64_t>::max)() || (!before && !after && commit.empty()))
        return std::nullopt;

    const TextInputIndex index(snapshot.utf8);
    const std::size_t low = std::min(snapshot.anchor, snapshot.focus);
    const std::size_t high = std::max(snapshot.anchor, snapshot.focus);
    const auto lowByte = index.utf8FromScalar(low - snapshot.origin);
    const auto highByte = index.utf8FromScalar(high - snapshot.origin);
    if (!lowByte || !highByte)
        return std::nullopt;

    std::size_t start = low;
    std::size_t end = high;
    std::size_t startByte = lowByte.offset;
    std::size_t endByte = highByte.offset;
    if (before || after)
    {
        if (!published || published->anchor != snapshot.anchor || published->focus != snapshot.focus ||
            before > lowByte.offset || after > snapshot.utf8.size() - highByte.offset)
            return std::nullopt;

        const auto oldLow = static_cast<std::size_t>(std::min(published->cursorByte, published->anchorByte));
        const auto oldHigh = static_cast<std::size_t>(std::max(published->cursorByte, published->anchorByte));
        if (before > oldLow || oldHigh > published->text.size() || after > published->text.size() - oldHigh)
            return std::nullopt;

        startByte -= before;
        endByte += after;
        const auto startScalar = index.scalarFromUtf8(startByte);
        const auto endScalar = index.scalarFromUtf8(endByte);
        const auto publishedStart = oldLow - before;
        const auto publishedEnd = oldHigh + after;
        // A serial may lag cursor-rectangle commits. Compare the actual affected bytes before using a deletion.
        if (!startScalar || !endScalar ||
            std::string_view(snapshot.utf8).substr(startByte, endByte - startByte) !=
                std::string_view(published->text).substr(publishedStart, publishedEnd - publishedStart))
            return std::nullopt;
        if (endScalar.offset > (std::numeric_limits<std::size_t>::max)() - snapshot.origin)
            return std::nullopt;
        start = snapshot.origin + startScalar.offset;
        end = snapshot.origin + endScalar.offset;
    }

    EditPlan result{{snapshot.revision, {}, {}, transactionId}, snapshot};
    if (!commit.empty())
    {
        const auto inserted = TextInputIndex(commit).scalarCount();
        const auto count = index.scalarCount().offset;
        const auto retained = count - (end - start);
        const auto remaining = (std::numeric_limits<std::size_t>::max)() - snapshot.origin;
        if (!inserted || retained > remaining || inserted.offset > remaining - retained)
            return std::nullopt;

        result.edit.operations.push_back({start, end, std::string(commit)});
        result.predicted.utf8.replace(startByte, endByte - startByte, commit);
        const auto caret = start + inserted.offset;
        result.edit.selectionAfter = {caret, caret};
    }
    else
    {
        // Delete outside the selection, in descending order so both offsets describe the current text.
        if (after)
        {
            result.edit.operations.push_back({high, end, {}});
            result.predicted.utf8.erase(highByte.offset, endByte - highByte.offset);
        }
        if (before)
        {
            result.edit.operations.push_back({start, low, {}});
            result.predicted.utf8.erase(startByte, lowByte.offset - startByte);
        }
        const auto shift = low - start;
        result.edit.selectionAfter = {snapshot.anchor - shift, snapshot.focus - shift};
    }

    ++result.predicted.revision;
    result.predicted.anchor = result.edit.selectionAfter.anchor;
    result.predicted.focus = result.edit.selectionAfter.focus;
    result.predicted.acknowledgedTransaction = transactionId;
    return result;
}

inline std::optional<TextInputSelection> preeditSelection(std::string_view text, std::int32_t begin, std::int32_t end)
{
    if (begin < 0 || end < 0)
        return std::nullopt;
    const TextInputIndex index(text);
    const auto anchor = index.scalarFromUtf8(static_cast<std::size_t>(begin));
    const auto focus = index.scalarFromUtf8(static_cast<std::size_t>(end));
    return anchor && focus ? std::optional<TextInputSelection>{{anchor.offset, focus.offset}} : std::nullopt;
}

}  // namespace cc::wayland_text_input
