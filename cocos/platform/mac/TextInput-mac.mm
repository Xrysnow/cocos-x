#include "platform/TextInputBackend.h"
#include "platform/TextInputIndex.h"
#include "platform/desktop/TextInputGLFW.h"
#include "base/ccUTF8.h"

#include <Cocoa/Cocoa.h>

#define GLFW_INCLUDE_NONE
#define GLFW_EXPOSE_NATIVE_COCOA
#include "glfw3.h"
#include "glfw3native.h"

#include <algorithm>
#include <deque>
#include <iterator>
#include <limits>
#include <utility>

namespace cc
{
class MacTextInputBackend;
}

@interface CCTextInputResponder : NSView <NSTextInputClient>
{
    cc::MacTextInputBackend* _backend;
    NSTextInputContext* _textContext;
}
- (instancetype)initWithBackend:(cc::MacTextInputBackend*)backend;
- (void)disconnect;
@end

namespace cc
{
namespace
{
constexpr NSRange unknownRange{NSNotFound, 0};

NSString* plainText(id value)
{
    if ([value isKindOfClass:[NSAttributedString class]])
        return [value string];
    return [value isKindOfClass:[NSString class]] ? (NSString*)value : nil;
}

std::optional<std::string> utf8String(id value)
{
    NSData* data = [plainText(value) dataUsingEncoding:NSUTF8StringEncoding allowLossyConversion:NO];
    if (!data)
        return {};
    if (![data length])
        return std::string{};
    return std::string(static_cast<const char*>([data bytes]), [data length]);
}

NSString* nativeString(std::string_view text)
{
    return [[[NSString alloc] initWithBytes:text.data() length:text.size() encoding:NSUTF8StringEncoding] autorelease];
}

bool containsRange(NSRange container, NSRange range)
{
    return container.location != NSNotFound && range.location != NSNotFound && range.location >= container.location &&
           range.location - container.location <= container.length &&
           range.length <= container.length - (range.location - container.location);
}

NSRect viewRect(NSView* view, const TextInputRect& rect)
{
    const NSRect bounds = [view bounds];
    const double y = [view isFlipped] ? NSMinY(bounds) + rect.y : NSMaxY(bounds) - rect.y - rect.height;
    return NSMakeRect(NSMinX(bounds) + rect.x, y, rect.width, rect.height);
}

std::optional<TextInputCommandAction> commandForSelector(SEL selector)
{
    using Command = TextInputCommandAction;
    if (selector == @selector(deleteBackward:)) return Command::backspace;
    if (selector == @selector(deleteForward:)) return Command::deleteForward;
    if (selector == @selector(moveLeft:) || selector == @selector(moveBackward:)) return Command::left;
    if (selector == @selector(moveRight:) || selector == @selector(moveForward:)) return Command::right;
    if (selector == @selector(moveUp:)) return Command::up;
    if (selector == @selector(moveDown:)) return Command::down;
    if (selector == @selector(moveToBeginningOfLine:)) return Command::lineStart;
    if (selector == @selector(moveToEndOfLine:)) return Command::lineEnd;
    if (selector == @selector(selectAll:)) return Command::selectAll;
    if (selector == @selector(insertNewline:)) return Command::insertNewline;
    if (selector == @selector(cancelOperation:)) return Command::cancel;
    return {};
}
}  // namespace

class MacTextInputBackend final : public TextInputBackend
{
public:
    MacTextInputBackend(GLFWwindow* glfwWindow, NSWindow* window) : _glfwWindow(glfwWindow), _window(window) {}
    ~MacTextInputBackend() override { removeResponder(); }

    TextInputCapabilities capabilities() const override
    {
        TextInputCapabilities capabilities;
        capabilities.anchor = true;
        capabilities.observePreedit = true;
        capabilities.rangeEdit = true;
        capabilities.cancelComposition = true;
        return capabilities;
    }

    TextInputError activate(const TextInputActivation& activation) override
    {
        NSView* content = [_window contentView];
        if (!content || ![NSThread isMainThread])
            return TextInputError::activationFailed;
        _sink = activation.sink;
        _observePreedit = activation.options.observePreedit && activation.options.purpose != TextInputPurpose::password;
        _area = activation.initial.area;
        _snapshot = activation.initial.snapshot;
        _responder = [[CCTextInputResponder alloc] initWithBackend:this];
        if (!_responder || ![_responder inputContext])
        {
            [_responder release];
            _responder = nil;
            _sink = {};
            return TextInputError::activationFailed;
        }
        _previousResponder = [[_window firstResponder] retain];
        [content addSubview:_responder];
        if (![_window makeFirstResponder:_responder])
        {
            removeResponder();
            _sink = {};
            return TextInputError::activationFailed;
        }
        return TextInputError::none;
    }

    void setArea(const std::optional<TextInputArea>& area) override
    {
        _area = area;
        [[_responder inputContext] invalidateCharacterCoordinates];
    }

    void updateSnapshot(const TextInputSnapshot& snapshot) override
    {
        // An acknowledgement of an earlier queued edit leaves later native edits projected.
        auto acknowledged = std::find_if(_projected.begin(), _projected.end(), [&](const auto& projected) {
            return projected.acknowledgedTransaction == snapshot.acknowledgedTransaction &&
                   projected.revision == snapshot.revision && projected.origin == snapshot.origin &&
                   projected.utf8 == snapshot.utf8 && projected.anchor == snapshot.anchor && projected.focus == snapshot.focus;
        });
        if (acknowledged == _projected.end())
        {
            if (_snapshot && (_snapshot->revision != snapshot.revision || _snapshot->origin != snapshot.origin ||
                              _snapshot->utf8 != snapshot.utf8 || _snapshot->anchor != snapshot.anchor ||
                              _snapshot->focus != snapshot.focus))
                cancelComposition();
            _projected.clear();
        }
        else
            _projected.erase(_projected.begin(), std::next(acknowledged));
        _snapshot = _projected.empty() ? snapshot : _projected.back();
    }

    TextInputError requestKeyboard(bool) override { return TextInputError::unsupported; }

    TextInputError cancelComposition() override
    {
        if (!_responder)
            return TextInputError::unsupported;
        _discarding = true;
        [[_responder inputContext] discardMarkedText];
        unmark();
        _discarding = false;
        return TextInputError::none;
    }

    void deactivate() override
    {
        if (_responder)
        {
            cancelComposition();
            removeResponder();
        }
        _sink.closed();
        _sink = {};
        _area.reset();
        _snapshot.reset();
        _projected.clear();
    }

    NSView* contentView() const { return [_window contentView]; }

    void keyDown(NSEvent* event)
    {
        _handlingKey = true;
        _forwardCommand = false;
        _producedText = false;
        const bool handled = [[_responder inputContext] handleEvent:event];
        _handlingKey = false;
        if (!_producedText && _marked.empty() && (!handled || _forwardCommand))
            [contentView() keyDown:event];
    }

    void command(SEL selector)
    {
        if (!_sink || !_marked.empty() || _discarding)
            return;
        if (_handlingKey)
        {
            // Cocoa has finished interpreting this key. Let GLFW supply the key and its modifiers.
            _forwardCommand = true;
            return;
        }
        if (const auto command = commandForSelector(selector))
            _sink.post(TextInputCommand{*command});
    }

    void insert(id value, NSRange replacement)
    {
        if (!_sink || _discarding)
            return;
        const auto text = utf8String(value);
        if (!text)
            return;
        _producedText = true;
        auto target = replacementTarget(replacement);
        const bool explicitRange = replacement.location != NSNotFound;
        const bool wasMarked = !_marked.empty();
        const bool localReplacement = wasMarked && containsRange(markedRange(), replacement);
        unmark();
        if (target)
            postEdit(*target, *text);
        else if ((!explicitRange || localReplacement) && !text->empty())
            TextInputGLFW::detail::postCommit(_glfwWindow, _sink, TextInputCommit{*text});
    }

    void mark(id value, NSRange selection, NSRange replacement)
    {
        if (!_sink || _discarding)
            return;
        auto text = utf8String(value);
        if (!text || text->empty())
        {
            unmark();
            return;
        }
        _producedText = true;
        const bool newMark = _marked.empty();
        _markedTarget = replacementTarget(replacement);
        _marked = std::move(*text);
        const TextInputIndex index(_marked);
        const auto count = index.scalarCount();
        _markedLength = count ? index.utf16FromScalar(count.offset).offset : 0;
        _markedSelection = containsRange(NSMakeRange(0, _markedLength), selection) ? selection : unknownRange;
        if (newMark)
        {
            TextInputState state;
            state.active = true;
            state.composing = TextInputKnowledge::yes;
            _sink.post(TextInputStateChanged{state});
        }
        if (_observePreedit)
        {
            TextInputPreedit event{_marked, std::nullopt,
                                   newMark ? TextInputPreeditPhase::began : TextInputPreeditPhase::updated};
            if (_markedSelection.location != NSNotFound)
            {
                const auto low = index.scalarFromUtf16(_markedSelection.location);
                const auto high = index.scalarFromUtf16(NSMaxRange(_markedSelection));
                if (low && high)
                    event.selection = TextInputSelection{low.offset, high.offset};
            }
            _sink.post(std::move(event));
        }
    }

    void unmark()
    {
        if (_marked.empty())
            return;
        _marked.clear();
        _markedLength = 0;
        _markedSelection = unknownRange;
        _markedTarget.reset();
        TextInputState state;
        state.active = true;
        state.composing = TextInputKnowledge::no;
        _sink.post(TextInputStateChanged{state});
        if (_observePreedit)
            _sink.post(TextInputPreedit{{}, std::nullopt, TextInputPreeditPhase::ended});
    }

    NSRange markedRange() const
    {
        if (_marked.empty())
            return unknownRange;
        const auto target = _markedTarget ? nativeRange(*_markedTarget) : unknownRange;
        return NSMakeRange(target.location == NSNotFound ? 0 : target.location, _markedLength);
    }

    NSRange selectedRange() const
    {
        const auto marked = markedRange();
        if (marked.location != NSNotFound && _markedSelection.location != NSNotFound)
            return NSMakeRange(marked.location + _markedSelection.location, _markedSelection.length);
        return _snapshot ? nativeRange({_snapshot->anchor, _snapshot->focus}) : unknownRange;
    }

    NSAttributedString* substring(NSRange range, NSRangePointer actualRange) const
    {
        if (actualRange)
            *actualRange = unknownRange;
        if (!_snapshot || _snapshot->origin != 0)
            return nil;
        NSString* text = nativeString(_snapshot->utf8);
        if (_markedTarget)
        {
            const NSRange target = nativeRange(*_markedTarget);
            if (containsRange(NSMakeRange(0, [text length]), target))
                text = [text stringByReplacingCharactersInRange:target withString:nativeString(_marked)];
        }
        if (!containsRange(NSMakeRange(0, [text length]), range))
            return nil;
        if (actualRange)
            *actualRange = range;
        return [[[NSAttributedString alloc] initWithString:[text substringWithRange:range]] autorelease];
    }

    NSRect screenRect(NSRangePointer actualRange) const
    {
        if (actualRange)
            *actualRange = selectedRange();
        NSView* content = contentView();
        if (!_area || !content)
            return NSZeroRect;
        auto caret = _area->caret;
        caret.width = std::max(1.0, caret.width);
        caret.height = std::max(1.0, caret.height);
        NSRect rect = viewRect(content, caret);
        if (_area->clip)
            rect = NSIntersectionRect(rect, viewRect(content, *_area->clip));
        if (NSIsEmptyRect(rect))
            return NSZeroRect;
        return [_window convertRectToScreen:[content convertRect:rect toView:nil]];
    }

private:
    void removeResponder()
    {
        if (!_responder)
            return;
        if ([_window firstResponder] == _responder)
        {
            if (![_window makeFirstResponder:_previousResponder])
                [_window makeFirstResponder:contentView()];
        }
        [_responder disconnect];
        [_responder removeFromSuperview];
        [_responder release];
        _responder = nil;
        [_previousResponder release];
        _previousResponder = nil;
    }

    NSRange nativeRange(TextInputSelection selection) const
    {
        if (!_snapshot || _snapshot->origin != 0)
            return unknownRange;
        const TextInputIndex index(_snapshot->utf8);
        const auto start = index.utf16FromScalar(std::min(selection.anchor, selection.focus));
        const auto end = index.utf16FromScalar(std::max(selection.anchor, selection.focus));
        return start && end ? NSMakeRange(start.offset, end.offset - start.offset) : unknownRange;
    }

    std::optional<TextInputSelection> replacementTarget(NSRange range) const
    {
        if (!_snapshot)
            return {};
        if (range.location == NSNotFound)
            return _markedTarget.value_or(TextInputSelection{_snapshot->anchor, _snapshot->focus});
        if (_markedTarget)
        {
            const auto mark = markedRange();
            if (containsRange(mark, range))
                return _markedTarget;
            if (_snapshot->origin != 0)
                return {};
            if (range.location >= NSMaxRange(mark))
            {
                const auto old = nativeRange(*_markedTarget);
                if (old.location == NSNotFound)
                    return {};
                range.location = NSMaxRange(old) + (range.location - NSMaxRange(mark));
            }
            else if (range.location >= mark.location || range.length > mark.location - range.location)
                return {};
        }
        if (_snapshot->origin != 0)
            return {};
        const TextInputIndex index(_snapshot->utf8);
        const auto count = index.scalarCount();
        if (!count)
            return {};
        const auto length = index.utf16FromScalar(count.offset);
        if (!length || !containsRange(NSMakeRange(0, length.offset), range))
            return {};
        const auto start = index.scalarFromUtf16(range.location);
        const auto end = index.scalarFromUtf16(NSMaxRange(range));
        if (!start || !end)
            return {};
        return TextInputSelection{start.offset, end.offset};
    }

    void postEdit(TextInputSelection target, const std::string& text)
    {
        const auto count = TextInputIndex(text).scalarCount();
        if (!count || _snapshot->revision == (std::numeric_limits<std::uint64_t>::max)())
            return;
        const auto start = std::min(target.anchor, target.focus);
        const auto end = std::max(target.anchor, target.focus);
        const TextInputIndex current(_snapshot->utf8);
        if (start < _snapshot->origin || count.offset > (std::numeric_limits<std::size_t>::max)() - start)
            return;
        const auto startByte = current.utf8FromScalar(start - _snapshot->origin);
        const auto endByte = current.utf8FromScalar(end - _snapshot->origin);
        if (!startByte || !endByte || (start == end && text.empty()))
            return;
        const auto after = start + count.offset;
        const auto transaction = ++_transaction;
        TextInputEdit edit{_snapshot->revision, {{start, end, text}}, {after, after}, transaction};
        if (_sink.post(std::move(edit)))
        {
            auto next = *_snapshot;
            ++next.revision;
            next.utf8.replace(startByte.offset, endByte.offset - startByte.offset, text);
            next.anchor = next.focus = after;
            next.acknowledgedTransaction = transaction;
            _projected.push_back(next);
            _snapshot = std::move(next);
        }
    }

    GLFWwindow* _glfwWindow;
    NSWindow* _window;
    CCTextInputResponder* _responder = nil;
    NSResponder* _previousResponder = nil;
    TextInputEventSink _sink;
    std::optional<TextInputArea> _area;
    std::optional<TextInputSnapshot> _snapshot;
    std::deque<TextInputSnapshot> _projected;
    std::optional<TextInputSelection> _markedTarget;
    std::string _marked;
    NSUInteger _markedLength = 0;
    NSRange _markedSelection = unknownRange;
    std::uint64_t _transaction = 0;
    bool _observePreedit = false;
    bool _discarding = false;
    bool _handlingKey = false;
    bool _forwardCommand = false;
    bool _producedText = false;
};

std::unique_ptr<TextInputBackend> createMacTextInputBackend(GLFWwindow* window)
{
    // Use the actual GLFW window and its existing Metal content view.
    NSWindow* native = glfwGetCocoaWindow(window);
    if (!native || ![native contentView])
        return {};
    return std::make_unique<MacTextInputBackend>(window, native);
}

bool isMacTextInputResponderActive(GLFWwindow* window)
{
    return [[glfwGetCocoaWindow(window) firstResponder] isKindOfClass:[CCTextInputResponder class]];
}

bool retainsMacTextInputFocus(GLFWwindow* window)
{
    NSWindow* native = glfwGetCocoaWindow(window);
    // The Character Viewer can temporarily take the GLFW key flag while AppKit
    // still associates the input context and first responder with this window.
    return native && [NSApp isActive] && [NSApp keyWindow] == native && [native isVisible] &&
           ![native isMiniaturized] && [[native firstResponder] isKindOfClass:[CCTextInputResponder class]];
}
}  // namespace cc

@implementation CCTextInputResponder
- (instancetype)initWithBackend:(cc::MacTextInputBackend*)backend
{
    self = [super initWithFrame:NSZeroRect];
    if (self)
    {
        _backend = backend;
        _textContext = [[NSTextInputContext alloc] initWithClient:self];
    }
    return self;
}
- (void)dealloc
{
    [_textContext release];
    [super dealloc];
}
- (void)disconnect
{
    _backend = nullptr;
    [_textContext release];
    _textContext = nil;
}
- (BOOL)acceptsFirstResponder { return YES; }
- (NSView*)hitTest:(NSPoint)point { return nil; }
- (NSTextInputContext*)inputContext { return _textContext; }
- (void)keyDown:(NSEvent*)event { if (_backend) _backend->keyDown(event); }
- (void)keyUp:(NSEvent*)event { if (_backend) [_backend->contentView() keyUp:event]; }
- (void)flagsChanged:(NSEvent*)event { if (_backend) [_backend->contentView() flagsChanged:event]; }
- (BOOL)performKeyEquivalent:(NSEvent*)event
{
    return _backend ? [_backend->contentView() performKeyEquivalent:event] : NO;
}
- (void)doCommandBySelector:(SEL)selector { if (_backend) _backend->command(selector); }
- (BOOL)hasMarkedText { return [self markedRange].location != NSNotFound; }
- (NSRange)markedRange { return _backend ? _backend->markedRange() : NSMakeRange(NSNotFound, 0); }
- (NSRange)selectedRange { return _backend ? _backend->selectedRange() : NSMakeRange(NSNotFound, 0); }
- (NSArray<NSAttributedStringKey>*)validAttributesForMarkedText { return @[]; }
- (void)unmarkText { if (_backend) _backend->unmark(); }
- (void)setMarkedText:(id)text selectedRange:(NSRange)selectedRange replacementRange:(NSRange)replacementRange
{
    if (_backend)
        _backend->mark(text, selectedRange, replacementRange);
}
- (void)insertText:(id)text replacementRange:(NSRange)range
{
    if (_backend)
        _backend->insert(text, range);
}
- (NSAttributedString*)attributedSubstringForProposedRange:(NSRange)range actualRange:(NSRangePointer)actualRange
{
    return _backend ? _backend->substring(range, actualRange) : nil;
}
- (NSUInteger)characterIndexForPoint:(NSPoint)point { return NSNotFound; }
- (NSRect)firstRectForCharacterRange:(NSRange)range actualRange:(NSRangePointer)actualRange
{
    return _backend ? _backend->screenRect(actualRange) : NSZeroRect;
}
@end
