#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>
#include <string>
#include <variant>
#include <vector>

namespace cc
{

using TextInputWindowId = std::uint64_t;
using TextInputSessionId = std::uint64_t;

enum class TextInputError
{
    none,
    invalidWindow,
    invalidArgument,
    invalidArea,
    invalidSnapshot,
    staleSnapshot,
    staleSession,
    unsupported,
    activationFailed,
};

enum class TextInputPurpose { text, name, email, url, phone, number, decimal, password };
enum class TextInputCapitalization { unspecified, none, sentences, words, characters };
enum class TextInputAction { unspecified, done, search, send, next, go };
enum class TextInputSpace { window, design };
enum class TextInputKnowledge { unknown, no, yes };
enum class TextInputPreeditPhase { began, updated, ended };
enum class TextInputCloseReason { requested, replaced, focusLost, activationFailed, nativeEnded };
enum class TextInputCommandAction
{
    backspace,
    deleteForward,
    left,
    right,
    up,
    down,
    lineStart,
    lineEnd,
    selectAll,
    insertNewline,
    done,
    search,
    send,
    next,
    go,
    cancel,
};

struct TextInputOptions
{
    TextInputPurpose purpose = TextInputPurpose::text;
    TextInputCapitalization capitalization = TextInputCapitalization::unspecified;
    TextInputAction returnAction = TextInputAction::unspecified;
    bool multiline = false;
    std::optional<bool> autocorrect;
    bool observePreedit = false;
    bool rangeEdit = false;
};

struct TextInputRect
{
    double x = 0;
    double y = 0;
    double width = 0;
    double height = 0;
};

struct TextInputArea
{
    TextInputRect caret;
    TextInputRect line;
    std::optional<TextInputRect> clip;
    TextInputSpace space = TextInputSpace::window;
};

// Offsets are zero-based Unicode scalar positions. Snapshot offsets are relative to the full text.
struct TextInputSelection
{
    std::size_t anchor = 0;
    std::size_t focus = 0;
};

struct TextInputSnapshot
{
    std::uint64_t revision = 0;
    std::size_t origin = 0;
    std::string utf8;
    std::size_t anchor = 0;
    std::size_t focus = 0;
    std::optional<std::uint64_t> acknowledgedTransaction;
};

struct TextInputInitialState
{
    std::optional<TextInputArea> area;
    std::optional<TextInputSnapshot> snapshot;
};

struct TextInputCapabilities
{
    bool anchor = false;
    bool observePreedit = false;
    bool rangeEdit = false;
    bool reconversion = false;
    bool keyboardVisibility = false;
    bool keyboardOcclusion = false;
    bool requestKeyboard = false;
    bool cancelComposition = false;
};

struct TextInputState
{
    bool active = false;
    TextInputKnowledge composing = TextInputKnowledge::unknown;
    TextInputKnowledge imeOpen = TextInputKnowledge::unknown;
    TextInputKnowledge keyboardVisible = TextInputKnowledge::unknown;
    // A zero-area rectangle represents a known absence of occlusion.
    std::optional<TextInputRect> occlusion;
};

struct TextInputFocus
{
    TextInputWindowId window = 0;
    TextInputSessionId session = 0;
    bool native = false;
    explicit operator bool() const { return session != 0; }
};

struct TextInputCommit { std::string text; };

struct TextInputReplace
{
    std::size_t start = 0;
    std::size_t end = 0;
    std::string utf8;
};

struct TextInputEdit
{
    std::uint64_t baseRevision = 0;
    std::vector<TextInputReplace> operations;
    TextInputSelection selectionAfter;
    std::uint64_t transactionId = 0;
};

struct TextInputPreedit
{
    std::string text;
    std::optional<TextInputSelection> selection;
    TextInputPreeditPhase phase = TextInputPreeditPhase::updated;
};

struct TextInputCommand { TextInputCommandAction action; };
struct TextInputStateChanged
{
    TextInputState state;
    // A platform keyboard transition may announce its destination before the observed state changes.
    std::optional<TextInputRect> targetOcclusion;
    std::optional<double> animationDuration;  // seconds
};
struct TextInputClosed { TextInputCloseReason reason; };

using TextInputPayload =
    std::variant<TextInputCommit, TextInputEdit, TextInputPreedit, TextInputCommand, TextInputStateChanged, TextInputClosed>;

struct TextInputEvent
{
    TextInputWindowId window = 0;
    TextInputSessionId session = 0;
    std::uint64_t sequence = 0;
    TextInputPayload payload;
};

}  // namespace cc
