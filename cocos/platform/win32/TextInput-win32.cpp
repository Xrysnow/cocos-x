#include "platform/TextInputBackend.h"
#include "platform/TextInputIndex.h"
#include "base/ccUTF8.h"

#include <Windows.h>
#include <commctrl.h>
#include <imm.h>

#define GLFW_INCLUDE_NONE
#define GLFW_EXPOSE_NATIVE_WIN32
#include "glfw3.h"
#include "glfw3native.h"

#include <algorithm>
#include <cmath>
#include <cstring>
#include <limits>
#include <utility>

namespace cc
{
namespace
{
thread_local GLFWwindow* consumedKeyWindow = nullptr;

UINT flushReconversionMessage()
{
    static const UINT message = RegisterWindowMessageW(L"LuaSTG-x.TextInput.FlushReconversion");
    return message;
}

std::optional<std::u16string> compositionString(HIMC context, DWORD field)
{
    if (!context)
        return std::nullopt;
    const LONG bytes = ImmGetCompositionStringW(context, field, nullptr, 0);
    if (bytes < 0 || bytes % sizeof(char16_t) != 0)
        return std::nullopt;
    std::u16string text(bytes / sizeof(char16_t), u'\0');
    if (bytes && ImmGetCompositionStringW(context, field, text.data(), bytes) != bytes)
        return std::nullopt;
    return text;
}

class ScopedInputContext
{
public:
    explicit ScopedInputContext(HWND window) : _window(window), _context(ImmGetContext(window)) {}
    ScopedInputContext(const ScopedInputContext&) = delete;
    ScopedInputContext& operator=(const ScopedInputContext&) = delete;
    ~ScopedInputContext()
    {
        if (_context)
            ImmReleaseContext(_window, _context);
    }

    HIMC get() const { return _context; }

private:
    HWND _window;
    HIMC _context;
};

LONG clientCoordinate(double value, LONG low, LONG high)
{
    return static_cast<LONG>(std::clamp(value, static_cast<double>(low), static_cast<double>(high)));
}

RECT clientRect(const TextInputRect& rect, const RECT& bounds)
{
    return {clientCoordinate(std::floor(rect.x), bounds.left, bounds.right),
            clientCoordinate(std::floor(rect.y), bounds.top, bounds.bottom),
            clientCoordinate(std::ceil(rect.x + rect.width), bounds.left, bounds.right),
            clientCoordinate(std::ceil(rect.y + rect.height), bounds.top, bounds.bottom)};
}

class Win32TextInputBackend final : public TextInputBackend
{
public:
    Win32TextInputBackend(GLFWwindow* glfwWindow, HWND window) : _glfwWindow(glfwWindow), _window(window) {}

    ~Win32TextInputBackend() override
    {
        if (_window && _subclassed)
        {
            RemoveWindowSubclass(_window, windowProc, SUBCLASS_ID);
            restoreAssociation();
        }
    }

    bool attach()
    {
        _subclassed = SetWindowSubclass(_window, windowProc, SUBCLASS_ID, reinterpret_cast<DWORD_PTR>(this));
        if (!_subclassed)
            return false;
        {
            const ScopedInputContext context(_window);
            _borrowedContext = context.get();
        }
        suspendAssociation();
        return true;
    }

    TextInputCapabilities capabilities() const override
    {
        TextInputCapabilities capabilities;
        capabilities.anchor = _borrowedContext != nullptr;
        capabilities.observePreedit = _borrowedContext != nullptr;
        capabilities.cancelComposition = _borrowedContext != nullptr;
        capabilities.rangeEdit = true;
        capabilities.reconversion = _borrowedContext != nullptr;
        return capabilities;
    }

    TextInputError activate(const TextInputActivation& activation) override
    {
        if (!_window)
            return TextInputError::activationFailed;
        _sink = activation.sink;
        _rangeEditing = activation.options.rangeEdit && activation.options.purpose != TextInputPurpose::password;
        if (activation.initial.snapshot)
            updateSnapshot(*activation.initial.snapshot);
        _observePreedit = activation.options.observePreedit && activation.options.purpose != TextInputPurpose::password;
        _state = {};
        _state.active = true;
        _area = activation.initial.area;
        restoreAssociation();
        const ScopedInputContext context(_window);
        publishOpenStatus(context.get());
        applyArea(context.get());
        return TextInputError::none;
    }

    void setArea(const std::optional<TextInputArea>& area) override
    {
        updateArea(area, false);
    }

    void geometryChanged(const std::optional<TextInputArea>& area) override
    {
        updateArea(area, true);
    }

    void updateArea(const std::optional<TextInputArea>& area, bool force)
    {
        _area = area;
        if (_window && _sink)
        {
            const ScopedInputContext context(_window);
            applyArea(context.get(), force);
        }
    }

    void updateSnapshot(const TextInputSnapshot& snapshot) override
    {
        if (!_rangeEditing)
            return;
        const auto epoch = _sink.snapshotEpoch();
        // The router only retains the epoch when the client acknowledged the exact projection.
        // The Win32 mirror can already contain later native input waiting in the same queue.
        if (_document && _document->epoch == epoch && snapshot.revision <= _document->revision)
            return;

        const bool staleReconversion = _reconversion.has_value();
        invalidateReconversion();
        Document document;
        if (!StringUtils::UTF8ToUTF32(snapshot.utf8, document.text))
        {
            _document.reset();
            _nativeDocument.reset();
            return;
        }
        document.origin = snapshot.origin;
        document.revision = snapshot.revision;
        document.epoch = epoch;
        document.selection = {snapshot.anchor, snapshot.focus};
        _document = std::move(document);
        _nativeDocument.reset();
        if (staleReconversion)
            cancelNativeComposition();
    }
    TextInputError requestKeyboard(bool) override { return TextInputError::unsupported; }

    TextInputError cancelComposition() override
    {
        if (!_window || _sink.session() == 0)
            return TextInputError::unsupported;
        flushReconversionCharacters();
        invalidateReconversion();
        return cancelNativeComposition();
    }

    void deactivate() override
    {
        if (_sink.session() == 0)
            return;
        cancelComposition();
        if (_window)
        {
            const ScopedInputContext context(_window);
            clearForms(context.get());
        }
        suspendAssociation();
        _area.reset();
        _document.reset();
        _nativeDocument.reset();
        _transaction = 0;
        _sink.closed();
        _sink = {};
    }

    static bool handleCharacter(GLFWwindow* window, unsigned int codepoint)
    {
        DWORD_PTR data = 0;
        auto handle = glfwGetWin32Window(window);
        if (!handle || !GetWindowSubclass(handle, windowProc, SUBCLASS_ID, &data))
            return false;
        auto& backend = *reinterpret_cast<Win32TextInputBackend*>(data);
        if (!backend._sink || !backend._document)
            return false;
        backend.flushReconversionCharacters();
        backend.invalidateReconversion();
        const char32_t scalar = static_cast<char32_t>(codepoint);
        backend.postEdit(backend.selectionTarget(), {&scalar, 1});
        return true;
    }

private:
    static constexpr UINT_PTR SUBCLASS_ID = 1;

    struct Document
    {
        std::u32string text;
        std::size_t origin = 0;
        std::uint64_t revision = 0;
        std::uint64_t epoch = 0;
        TextInputSelection selection;
    };

    struct NativeDocument
    {
        std::u16string text;
        TextInputIndex index;
    };

    struct EditTarget
    {
        std::size_t start;
        std::size_t end;
        std::uint64_t revision;
        std::uint64_t epoch;
    };

    EditTarget selectionTarget() const
    {
        return {std::min(_document->selection.anchor, _document->selection.focus),
                std::max(_document->selection.anchor, _document->selection.focus),
                _document->revision, _document->epoch};
    }

    bool targetCurrent(const EditTarget& target) const
    {
        return _document && target.epoch == _document->epoch && target.epoch == _sink.snapshotEpoch() &&
               target.revision == _document->revision;
    }

    const NativeDocument* nativeDocument()
    {
        if (!_document)
            return nullptr;
        if (!_nativeDocument)
        {
            if (_document->text.find(U'\0') != std::u32string::npos)
                return nullptr;
            std::u16string wide;
            std::string utf8;
            if (!StringUtils::UTF32ToUTF16(_document->text, wide) || !StringUtils::UTF32ToUTF8(_document->text, utf8))
                return nullptr;
            _nativeDocument.emplace(NativeDocument{std::move(wide), TextInputIndex(utf8)});
        }
        return &*_nativeDocument;
    }

    void postEdit(const EditTarget& target, std::u32string_view replacement)
    {
        if (!targetCurrent(target) || target.start < _document->origin || target.end < target.start ||
            target.end - _document->origin > _document->text.size() ||
            _document->revision == (std::numeric_limits<std::uint64_t>::max)())
            return;
        const auto retained = _document->text.size() - (target.end - target.start);
        const auto available = (std::numeric_limits<std::size_t>::max)() - _document->origin;
        if (replacement.size() > available - retained)
            return;
        if (target.start == target.end && replacement.empty())
            return;
        std::string utf8;
        if (!StringUtils::UTF32ToUTF8(replacement, utf8))
            return;

        const auto caret = target.start + replacement.size();
        TextInputEdit edit{target.revision, {{target.start, target.end, std::move(utf8)}}, {caret, caret}, ++_transaction};
        if (_sink.post(std::move(edit), target.epoch))
        {
            _document->text.replace(target.start - _document->origin, target.end - target.start, replacement);
            _document->selection = {caret, caret};
            ++_document->revision;
            _nativeDocument.reset();
        }
    }

    TextInputError cancelNativeComposition()
    {
        if (!_window)
            return TextInputError::unsupported;
        const ScopedInputContext context(_window);
        const bool cancelled = context.get() && ImmNotifyIME(context.get(), NI_COMPOSITIONSTR, CPS_CANCEL, 0);
        endComposition();
        return cancelled ? TextInputError::none : TextInputError::unsupported;
    }

    void invalidateReconversion()
    {
        if (_reconversion)
            _discardReconversionResult = true;
        _reconversion.reset();
        _reconversionCharacters.clear();
    }

    LRESULT supplyDocument(bool reconvert, LPARAM address)
    {
        if (!_borrowedContext || !_document || _document->epoch != _sink.snapshotEpoch())
            return 0;
        const ScopedInputContext context(_window);
        if (!context.get())
            return 0;
        const auto selection = reconvert || !_reconversion ? selectionTarget() : *_reconversion;
        if (!targetCurrent(selection) || (reconvert && selection.start == selection.end))
            return 0;

        const auto* native = nativeDocument();
        if (!native || native->text.size() >
                           ((std::numeric_limits<DWORD>::max)() - sizeof(RECONVERTSTRING)) / sizeof(char16_t) - 1)
            return 0;
        const auto start = native->index.utf16FromScalar(selection.start - _document->origin);
        const auto end = native->index.utf16FromScalar(selection.end - _document->origin);
        if (!start || !end)
            return 0;

        const auto size = static_cast<DWORD>(sizeof(RECONVERTSTRING) + (native->text.size() + 1) * sizeof(char16_t));
        if (!address)
            return size;
        auto* buffer = reinterpret_cast<RECONVERTSTRING*>(address);
        if (buffer->dwSize < size)
            return 0;

        const auto length = static_cast<DWORD>(end.offset - start.offset);
        const auto offset = static_cast<DWORD>(start.offset * sizeof(char16_t));
        *buffer = {size, 0, static_cast<DWORD>(native->text.size()), sizeof(RECONVERTSTRING), length, offset, length, offset};
        std::memcpy(reinterpret_cast<char*>(buffer) + buffer->dwStrOffset, native->text.c_str(),
                    (native->text.size() + 1) * sizeof(char16_t));

        if (reconvert)
        {
            _reconversion = selection;
            _reconversionCharacters.clear();
            _discardReconversionResult = false;
        }
        return size;
    }

    LRESULT confirmReconversion(LPARAM address)
    {
        if (!address || !_reconversion || !targetCurrent(*_reconversion))
            return FALSE;
        const auto* native = nativeDocument();
        const auto* buffer = reinterpret_cast<const RECONVERTSTRING*>(address);
        if (!native || buffer->dwSize < sizeof(RECONVERTSTRING) || buffer->dwVersion != 0 ||
            buffer->dwStrOffset < sizeof(RECONVERTSTRING) ||
            buffer->dwStrOffset % sizeof(char16_t) != 0 || buffer->dwStrOffset > buffer->dwSize ||
            buffer->dwStrLen != native->text.size() ||
            buffer->dwStrLen > (buffer->dwSize - buffer->dwStrOffset) / sizeof(char16_t) ||
            std::memcmp(reinterpret_cast<const char*>(buffer) + buffer->dwStrOffset, native->text.data(),
                        native->text.size() * sizeof(char16_t)) != 0)
            return FALSE;

        const auto scalarRange = [&](DWORD offset, DWORD length) -> std::optional<TextInputSelection> {
            if (offset % sizeof(char16_t) != 0)
                return std::nullopt;
            const auto first = offset / sizeof(char16_t);
            if (first > native->text.size() || length > native->text.size() - first)
                return std::nullopt;
            const auto start = native->index.scalarFromUtf16(first);
            const auto end = native->index.scalarFromUtf16(first + length);
            if (!start || !end)
                return std::nullopt;
            return TextInputSelection{_document->origin + start.offset, _document->origin + end.offset};
        };
        const auto composition = scalarRange(buffer->dwCompStrOffset, buffer->dwCompStrLen);
        const auto target = scalarRange(buffer->dwTargetStrOffset, buffer->dwTargetStrLen);
        if (!composition || !target || composition->anchor == composition->focus ||
            target->anchor < composition->anchor || target->focus > composition->focus)
            return FALSE;

        // The result replaces the complete composition. The IME's target only identifies a clause.
        _reconversion->start = composition->anchor;
        _reconversion->end = composition->focus;
        return TRUE;
    }

    bool claimCompositionResult()
    {
        if (_discardReconversionResult)
            return true;
        if (!_document)
            return false;
        const ScopedInputContext context(_window);
        const auto result = compositionString(context.get(), GCS_RESULTSTR);
        std::u32string replacement;
        if (!result || !StringUtils::UTF16ToUTF32(*result, replacement))
            return false;

        const auto target = _reconversion.value_or(selectionTarget());
        _reconversion.reset();
        _reconversionCharacters.clear();
        postEdit(target, replacement);
        return true;
    }

    bool queueReconversionCharacter(WPARAM value)
    {
        if (_discardReconversionResult)
            return true;
        if (!_reconversion)
            return false;
        if (!targetCurrent(*_reconversion))
        {
            invalidateReconversion();
            return true;
        }
        if (value == 0 || value > 0xffff)
            return true;
        if (_reconversionCharacters.empty())
        {
            // A legacy IME can deliver a result as several UTF-16 WM_IME_CHAR messages.
            // Drain the batch at the native queue boundary if no explicit end arrives first.
            const UINT message = flushReconversionMessage();
            if (message)
                PostMessageW(_window, message, ++_reconversionSequence, 0);
        }
        _reconversionCharacters.push_back(static_cast<char16_t>(value));
        return true;
    }

    void flushReconversionCharacters()
    {
        if (_reconversionCharacters.empty())
            return;
        const auto target = std::exchange(_reconversion, std::nullopt);
        std::u32string replacement;
        if (target && StringUtils::UTF16ToUTF32(_reconversionCharacters, replacement))
            postEdit(*target, replacement);
        _reconversionCharacters.clear();
    }

    void finishReconversion()
    {
        flushReconversionCharacters();
        if (!_reconversion)
            return;

        // Microsoft Korean IME can end the composition just before its queued result.
        // Preserve the offered range only for the next result on this same window.
        MSG pending;
        if (!PeekMessageW(&pending, _window, WM_IME_STARTCOMPOSITION, WM_IME_COMPOSITION, PM_NOREMOVE | PM_NOYIELD) ||
            pending.message != WM_IME_COMPOSITION || !(pending.lParam & GCS_RESULTSTR))
            invalidateReconversion();
    }

    void suspendAssociation()
    {
        if (!_window || !_borrowedContext || _associationSuspended)
            return;
        {
            const ScopedInputContext context(_window);
            if (context.get() != _borrowedContext)
                return;
        }
        _associationSuspended = ImmAssociateContextEx(_window, nullptr, 0) != FALSE;
    }

    void restoreAssociation()
    {
        if (_associationSuspended && ImmAssociateContextEx(_window, _borrowedContext, 0))
            _associationSuspended = false;
    }

    void clearForms(HIMC context)
    {
        if (_compositionBounds && context)
        {
            COMPOSITIONFORM composition{CFS_DEFAULT, {}, {}};
            ImmSetCompositionWindow(context, &composition);
        }
        if (context)
        {
            for (DWORD index = 0, lists = _positionedCandidates; lists != 0; ++index, lists >>= 1)
            {
                if (lists & 1)
                {
                    CANDIDATEFORM candidate{index, CFS_DEFAULT, {}, {}};
                    ImmSetCandidateWindow(context, &candidate);
                }
            }
        }
        _compositionBounds.reset();
        _candidateExclusion = {};
        _positionedCandidates = 0;
    }

    void applyArea(HIMC context, bool force = true, DWORD candidateLists = 1)
    {
        if (!context)
            return;
        RECT bounds;
        if (!_area || !GetClientRect(_window, &bounds) || IsRectEmpty(&bounds))
        {
            clearForms(context);
            return;
        }
        // GLFW client coordinates and IMM coordinates use the same Win32 client space.
        if (_area->clip)
        {
            bounds = clientRect(*_area->clip, bounds);
            if (IsRectEmpty(&bounds))
            {
                clearForms(context);
                return;
            }
        }
        const RECT caret = clientRect(_area->caret, bounds);
        const RECT line = clientRect(_area->line, bounds);
        const LONG x = std::min(caret.left, bounds.right - 1);
        const LONG y = std::min(caret.top, bounds.bottom - 1);
        COMPOSITIONFORM composition{CFS_RECT, {x, y}, {x, y, bounds.right, bounds.bottom}};
        const RECT exclude{std::min(x, line.left), std::min(y, line.top),
                           std::max({x + 1, caret.right, line.right}),
                           std::max({y + 1, caret.bottom, line.bottom})};
        const bool compositionChanged = !_compositionBounds || !EqualRect(&*_compositionBounds, &composition.rcArea);
        if ((compositionChanged || force) && ImmSetCompositionWindow(context, &composition))
            _compositionBounds = composition.rcArea;

        DWORD lists = candidateLists & ~_positionedCandidates;
        if (compositionChanged || force || !EqualRect(&_candidateExclusion, &exclude))
            lists = (candidateLists | _positionedCandidates);
        for (DWORD index = 0; lists != 0; ++index, lists >>= 1)
        {
            if (lists & 1)
            {
                CANDIDATEFORM candidate{index, CFS_EXCLUDE, {x, exclude.bottom}, exclude};
                if (ImmSetCandidateWindow(context, &candidate))
                    _positionedCandidates |= DWORD{1} << index;
            }
        }
        _candidateExclusion = exclude;
    }

    void publishOpenStatus(HIMC context)
    {
        const TextInputKnowledge open = !context ? TextInputKnowledge::unknown :
            ImmGetOpenStatus(context) ? TextInputKnowledge::yes : TextInputKnowledge::no;
        if (_state.imeOpen != open)
        {
            _state.imeOpen = open;
            _sink.post(TextInputStateChanged{_state});
        }
    }

    void setComposing(TextInputKnowledge composing)
    {
        if (_state.composing != composing)
        {
            _state.composing = composing;
            _sink.post(TextInputStateChanged{_state});
        }
    }

    void beginComposition()
    {
        if (_state.composing == TextInputKnowledge::yes)
            return;
        setComposing(TextInputKnowledge::yes);
        if (_observePreedit)
            _sink.post(TextInputPreedit{{}, std::nullopt, TextInputPreeditPhase::began});
    }

    void endComposition()
    {
        if (_state.composing != TextInputKnowledge::yes)
            return;
        setComposing(TextInputKnowledge::no);
        if (_observePreedit)
            _sink.post(TextInputPreedit{{}, std::nullopt, TextInputPreeditPhase::ended});
    }

    void updateComposition(LPARAM flags)
    {
        if (!(flags & (GCS_COMPSTR | GCS_CURSORPOS)))
        {
            if (flags == 0)
                invalidateReconversion();
            if (flags == 0 || (flags & GCS_RESULTSTR))
                endComposition();
            return;
        }
        const ScopedInputContext context(_window);
        if (!context.get())
            return;
        beginComposition();
        if (!_observePreedit)
            return;

        const auto wide = compositionString(context.get(), GCS_COMPSTR);
        TextInputPreedit preedit;
        if (!wide || !StringUtils::UTF16ToUTF8(*wide, preedit.text))
            return;
        const LONG cursor = ImmGetCompositionStringW(context.get(), GCS_CURSORPOS, nullptr, 0);
        if (cursor >= 0)
        {
            const auto scalar = TextInputIndex(preedit.text).scalarFromUtf16(cursor);
            if (scalar)
                preedit.selection = TextInputSelection{scalar.offset, scalar.offset};
        }
        _sink.post(std::move(preedit));
    }

    void observeMessage(UINT message, WPARAM wParam, LPARAM lParam)
    {
        switch (message)
        {
        case WM_IME_STARTCOMPOSITION:
        {
            flushReconversionCharacters();
            _discardReconversionResult = false;
            const ScopedInputContext context(_window);
            applyArea(context.get());
            beginComposition();
            break;
        }
        case WM_IME_COMPOSITION: updateComposition(lParam); break;
        case WM_IME_ENDCOMPOSITION:
            finishReconversion();
            endComposition();
            break;
        case WM_INPUTLANGCHANGE:
        {
            const ScopedInputContext context(_window);
            flushReconversionCharacters();
            invalidateReconversion();
            endComposition();
            publishOpenStatus(context.get());
            applyArea(context.get());
            break;
        }
        case WM_IME_NOTIFY:
            if (wParam == IMN_SETOPENSTATUS || wParam == IMN_OPENCANDIDATE)
            {
                const ScopedInputContext context(_window);
                if (wParam == IMN_SETOPENSTATUS)
                    publishOpenStatus(context.get());
                else
                    applyArea(context.get(), true, static_cast<DWORD>(lParam));
            }
            break;
        default: break;
        }
    }

    static LRESULT CALLBACK windowProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam,
                                       UINT_PTR id, DWORD_PTR data)
    {
        auto& backend = *reinterpret_cast<Win32TextInputBackend*>(data);
        if (message == WM_NCDESTROY)
        {
            RemoveWindowSubclass(window, windowProc, id);
            backend._window = nullptr;
            return DefSubclassProc(window, message, wParam, lParam);
        }
        if (message == flushReconversionMessage() && message != 0)
        {
            if (wParam == backend._reconversionSequence)
                backend.flushReconversionCharacters();
            return 0;
        }
        if (backend._sink)
        {
            if (message == WM_IME_REQUEST)
            {
                switch (wParam)
                {
                case IMR_RECONVERTSTRING: return backend.supplyDocument(true, lParam);
                case IMR_DOCUMENTFEED: return backend.supplyDocument(false, lParam);
                case IMR_CONFIRMRECONVERTSTRING: return backend.confirmReconversion(lParam);
                default: break;
                }
            }
            if (message == WM_IME_CHAR && backend.queueReconversionCharacter(wParam))
                return 0;
            if ((message == WM_KEYDOWN || message == WM_SYSKEYDOWN) && wParam != VK_PROCESSKEY)
                backend.flushReconversionCharacters();

            const bool claimed = message == WM_IME_COMPOSITION && (lParam & GCS_RESULTSTR) &&
                                 backend.claimCompositionResult();
            backend.observeMessage(message, wParam, lParam);
            if (claimed)
            {
                // Keep native presentation/preedit handling. The default process must not emit
                // WM_IME_CHAR for the same result already posted as one text edit.
                constexpr LPARAM resultFlags = GCS_RESULTSTR | GCS_RESULTCLAUSE | GCS_RESULTREADSTR | GCS_RESULTREADCLAUSE;
                lParam &= ~resultFlags;
            }
        }

        // GLFW sees the scancode even when IMM has rewritten a keydown to VK_PROCESSKEY.
        // Suppress its editing/game meaning for this dispatch while preserving the native chain.
        if (backend._sink && wParam == VK_PROCESSKEY && (message == WM_KEYDOWN || message == WM_SYSKEYDOWN))
        {
            auto previous = std::exchange(consumedKeyWindow, backend._glfwWindow);
            const auto result = DefSubclassProc(window, message, wParam, lParam);
            consumedKeyWindow = previous;
            return result;
        }
        return DefSubclassProc(window, message, wParam, lParam);
    }

    GLFWwindow* _glfwWindow;
    HWND _window;
    HIMC _borrowedContext = nullptr;
    bool _subclassed = false;
    bool _associationSuspended = false;
    bool _observePreedit = false;
    bool _rangeEditing = false;
    bool _discardReconversionResult = false;
    TextInputEventSink _sink;
    std::optional<Document> _document;
    std::optional<NativeDocument> _nativeDocument;
    std::optional<EditTarget> _reconversion;
    std::u16string _reconversionCharacters;
    WPARAM _reconversionSequence = 0;
    std::uint64_t _transaction = 0;
    std::optional<TextInputArea> _area;
    std::optional<RECT> _compositionBounds;
    RECT _candidateExclusion{};
    DWORD _positionedCandidates = 0;
    TextInputState _state;
};
}  // namespace

std::unique_ptr<TextInputBackend> createWin32TextInputBackend(GLFWwindow* window)
{
    const HWND handle = glfwGetWin32Window(window);
    if (!handle)
        return {};
    auto backend = std::make_unique<Win32TextInputBackend>(window, handle);
    if (!backend->attach())
        return {};
    return backend;
}

bool isWin32ImeKeyConsumed(GLFWwindow* window)
{
    return consumedKeyWindow == window && window != nullptr;
}

bool handleWin32TextCharacter(GLFWwindow* window, unsigned int codepoint)
{
    return Win32TextInputBackend::handleCharacter(window, codepoint);
}

}  // namespace cc
