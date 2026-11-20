#import <UIKit/UIKit.h>

#include "platform/ios/TextInput-ios.h"

#include "base/ccUTF8.h"
#include "platform/TextInputBackend.h"
#include "platform/TextInputIndex.h"
#include "platform/ios/EAGLView-ios.h"

#include <algorithm>
#include <limits>
#include <utility>

#if !TARGET_OS_TV
namespace
{
using namespace cc;

std::string utf8String(NSString* string)
{
    NSData* data = [string dataUsingEncoding:NSUTF8StringEncoding];
    return data.length ? std::string(static_cast<const char*>(data.bytes), data.length) : std::string{};
}

NSString* nativeString(std::string_view utf8)
{
    if (utf8.empty())
        return @"";
    return [[NSString alloc] initWithBytes:utf8.data() length:utf8.size() encoding:NSUTF8StringEncoding];
}

CGRect nativeRect(const TextInputRect& rect)
{
    return CGRectMake(rect.x, rect.y, rect.width, rect.height);
}

UIKeyboardType keyboardType(TextInputPurpose purpose)
{
    switch (purpose)
    {
    case TextInputPurpose::email: return UIKeyboardTypeEmailAddress;
    case TextInputPurpose::url: return UIKeyboardTypeURL;
    case TextInputPurpose::phone: return UIKeyboardTypePhonePad;
    case TextInputPurpose::number: return UIKeyboardTypeNumberPad;
    case TextInputPurpose::decimal: return UIKeyboardTypeDecimalPad;
    default: return UIKeyboardTypeDefault;
    }
}

UIReturnKeyType returnKeyType(TextInputAction action)
{
    switch (action)
    {
    case TextInputAction::done: return UIReturnKeyDone;
    case TextInputAction::search: return UIReturnKeySearch;
    case TextInputAction::send: return UIReturnKeySend;
    case TextInputAction::next: return UIReturnKeyNext;
    case TextInputAction::go: return UIReturnKeyGo;
    case TextInputAction::unspecified: return UIReturnKeyDefault;
    }
    return UIReturnKeyDefault;
}

UITextAutocapitalizationType capitalizationType(TextInputCapitalization capitalization)
{
    switch (capitalization)
    {
    case TextInputCapitalization::characters: return UITextAutocapitalizationTypeAllCharacters;
    case TextInputCapitalization::words: return UITextAutocapitalizationTypeWords;
    case TextInputCapitalization::sentences: return UITextAutocapitalizationTypeSentences;
    default: return UITextAutocapitalizationTypeNone;
    }
}

std::optional<TextInputReplace> replacement(const TextInputSnapshot& snapshot, std::string_view current)
{
    std::u32string before;
    std::u32string after;
    if (!StringUtils::UTF8ToUTF32(snapshot.utf8, before) || !StringUtils::UTF8ToUTF32(current, after))
        return std::nullopt;

    std::size_t prefix = 0;
    while (prefix < before.size() && prefix < after.size() && before[prefix] == after[prefix])
        ++prefix;
    auto beforeEnd = before.size();
    auto afterEnd = after.size();
    while (beforeEnd > prefix && afterEnd > prefix && before[beforeEnd - 1] == after[afterEnd - 1])
    {
        --beforeEnd;
        --afterEnd;
    }
    TextInputReplace op{snapshot.origin + prefix, snapshot.origin + beforeEnd, {}};
    if (!StringUtils::UTF32ToUTF8(std::u32string_view(after).substr(prefix, afterEnd - prefix), op.utf8))
        return std::nullopt;
    return op;
}
}  // namespace

@interface CCSessionTextInputView : UITextView <UITextViewDelegate>
- (instancetype)initWithHost:(CCEAGLView*)host;
- (BOOL)start:(const cc::TextInputActivation&)activation;
- (void)finish;
- (void)updateArea:(const std::optional<cc::TextInputArea>&)area;
- (void)updateSnapshot:(const cc::TextInputSnapshot&)snapshot;
- (BOOL)requestKeyboard:(BOOL)visible;
- (void)cancelComposition;
- (void)clearSession;
- (BOOL)dispatchReturnForText:(NSString*)text;
- (void)flushChanges;
- (void)installSnapshot;
- (void)observeMark;
- (void)scheduleFlush;
- (void)updateMarkedLabel;
@end

@implementation CCSessionTextInputView
{
    __weak CCEAGLView* _host;
    UILabel* _markedLabel;
    UIView* _keyboardPlaceholder;
    cc::TextInputEventSink _sink;
    cc::TextInputOptions _options;
    std::optional<cc::TextInputArea> _area;
    std::optional<cc::TextInputSnapshot> _snapshot;
    cc::TextInputState _state;
    std::uint64_t _snapshotEpoch;
    std::uint64_t _nextTransaction;
    unsigned int _nativeDepth;
    bool _programmatic;
    bool _ending;
    bool _flushScheduled;
    bool _observedMark;
}

- (instancetype)initWithHost:(CCEAGLView*)host
{
    if ((self = [super initWithFrame:host.bounds]))
    {
        _host = host;
        self.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight;
        self.backgroundColor = UIColor.clearColor;
        self.textColor = UIColor.clearColor;
        self.tintColor = UIColor.clearColor;
        self.scrollEnabled = NO;
        self.accessibilityElementsHidden = YES;
        self.textContainerInset = UIEdgeInsetsZero;
        self.textContainer.lineFragmentPadding = 0;

        _markedLabel = [[UILabel alloc] initWithFrame:CGRectZero];
        _markedLabel.hidden = YES;
        _markedLabel.userInteractionEnabled = NO;
        _markedLabel.numberOfLines = 1;
        [self addSubview:_markedLabel];
        _keyboardPlaceholder = [[UIView alloc] initWithFrame:CGRectZero];

        NSNotificationCenter* notifications = NSNotificationCenter.defaultCenter;
        for (NSString* name in @[UIKeyboardWillShowNotification, UIKeyboardWillChangeFrameNotification,
                                 UIKeyboardWillHideNotification, UIKeyboardDidShowNotification,
                                 UIKeyboardDidChangeFrameNotification, UIKeyboardDidHideNotification])
            [notifications addObserver:self selector:@selector(keyboardChanged:) name:name object:nil];
    }
    return self;
}

- (void)dealloc
{
    [NSNotificationCenter.defaultCenter removeObserver:self];
}

- (BOOL)pointInside:(CGPoint)point withEvent:(UIEvent*)event
{
    return NO;
}

- (BOOL)start:(const cc::TextInputActivation&)activation
{
    CCEAGLView* host = _host;
    if (!host)
        return NO;

    _sink = activation.sink;
    _options = activation.options;
    _nextTransaction = 1;
    _snapshotEpoch = 0;
    _snapshot.reset();
    _state = {};
    _observedMark = false;
    _flushScheduled = false;
    self.delegate = self;
    self.keyboardType = keyboardType(_options.purpose);
    self.returnKeyType = returnKeyType(_options.returnAction);
    self.autocapitalizationType = capitalizationType(_options.capitalization);
    self.secureTextEntry = _options.purpose == cc::TextInputPurpose::password;
    self.autocorrectionType = UITextAutocorrectionTypeNo;
    self.spellCheckingType = UITextSpellCheckingTypeNo;
    self.inputView = _keyboardPlaceholder;

    if (activation.initial.snapshot)
        [self updateSnapshot:*activation.initial.snapshot];
    else
        [self installSnapshot];
    [self updateArea:activation.initial.area];
    self.frame = host.bounds;
    [host addSubview:self];
    if (!self.window || self.isFirstResponder)
        return YES;

    [self clearSession];
    return NO;
}

- (void)didMoveToWindow
{
    [super didMoveToWindow];
    if (_sink && !_ending && self.window && !self.isFirstResponder)
        [self becomeFirstResponder];
}

- (void)clearSession
{
    _sink = {};
    _snapshot.reset();
    _area.reset();
    _flushScheduled = false;
    self.delegate = nil;
    _markedLabel.hidden = YES;
    _markedLabel.text = nil;
    self.text = @"";
    [self removeFromSuperview];
}

- (void)finish
{
    if (!_sink.session())
        return;
    _ending = true;
    [self flushChanges];
    [self resignFirstResponder];
    [self flushChanges];
    const auto sink = _sink;
    [self clearSession];
    _ending = false;
    sink.closed();
}

- (void)textViewDidEndEditing:(UITextView*)textView
{
    if (!_sink || _ending)
        return;
    [self flushChanges];
    const auto sink = _sink;
    [self clearSession];
    sink.closed(cc::TextInputCloseReason::nativeEnded);
}

- (void)updateArea:(const std::optional<cc::TextInputArea>&)area
{
    _area = area;
    [self updateMarkedLabel];
}

- (CGRect)caretRectForPosition:(UITextPosition*)position
{
    if (_area && _host)
        return [self convertRect:nativeRect(_area->caret) fromView:_host];
    return [super caretRectForPosition:position];
}

- (CGRect)firstRectForRange:(UITextRange*)range
{
    if (_area && _host)
        return [self convertRect:nativeRect(_area->caret) fromView:_host];
    return [super firstRectForRange:range];
}

- (void)updateMarkedLabel
{
    UITextRange* mark = self.markedTextRange;
    NSString* text = mark ? [self textInRange:mark] : nil;
    _markedLabel.hidden = !_area || !text.length || self.secureTextEntry;
    if (_markedLabel.hidden)
    {
        _markedLabel.text = nil;
        return;
    }
    const auto& caret = _area->caret;
    _markedLabel.font = [UIFont systemFontOfSize:std::max(1.0, caret.height * 0.8)];
    _markedLabel.text = text;
    const CGRect anchor = [self convertRect:nativeRect(caret) fromView:_host];
    CGSize label = [_markedLabel sizeThatFits:CGSizeMake(CGRectGetWidth(self.bounds), caret.height)];
    _markedLabel.frame = CGRectMake(anchor.origin.x, anchor.origin.y, label.width, caret.height);
}

- (void)installSnapshot
{
    _programmatic = true;
    [super unmarkText];
    self.text = _snapshot ? nativeString(_snapshot->utf8) : @"";
    if (_snapshot)
    {
        const cc::TextInputIndex index(_snapshot->utf8);
        const auto start = index.utf16FromScalar(std::min(_snapshot->anchor, _snapshot->focus) - _snapshot->origin);
        const auto end = index.utf16FromScalar(std::max(_snapshot->anchor, _snapshot->focus) - _snapshot->origin);
        if (start && end)
            self.selectedRange = NSMakeRange(start.offset, end.offset - start.offset);
    }
    [self.undoManager removeAllActions];
    _programmatic = false;
    [self updateMarkedLabel];
}

- (void)updateSnapshot:(const cc::TextInputSnapshot&)snapshot
{
    const auto epoch = _sink.snapshotEpoch();
    if (_snapshot && epoch == _snapshotEpoch && snapshot.revision <= _snapshot->revision)
        return;

    _snapshotEpoch = epoch;
    _snapshot = snapshot;
    self.autocorrectionType = _options.autocorrect.value_or(true) ? UITextAutocorrectionTypeDefault
                                                                   : UITextAutocorrectionTypeNo;
    self.spellCheckingType = _options.autocorrect.value_or(true) ? UITextSpellCheckingTypeDefault
                                                                    : UITextSpellCheckingTypeNo;
    [self installSnapshot];
    [self observeMark];
}

- (BOOL)requestKeyboard:(BOOL)visible
{
    if (!_sink)
        return NO;
    self.inputView = visible ? nil : _keyboardPlaceholder;
    if (!self.window)
        return YES;
    if (self.isFirstResponder)
    {
        [self reloadInputViews];
        return YES;
    }
    return [self becomeFirstResponder];
}

- (void)cancelComposition
{
    if (!_sink || !self.markedTextRange)
        return;
    [self installSnapshot];
    [self observeMark];
}

- (BOOL)textView:(UITextView*)textView shouldChangeTextInRange:(NSRange)range replacementText:(NSString*)text
{
    return ![self dispatchReturnForText:text];
}

- (BOOL)dispatchReturnForText:(NSString*)text
{
    if (_sink && !_programmatic && !_options.multiline && !self.markedTextRange && [text isEqualToString:@"\n"])
    {
        _sink.post(cc::TextInputCommand{cc::TextInputCommandAction::insertNewline});
        return YES;
    }
    return NO;
}

- (void)insertText:(NSString*)text
{
    if ([self dispatchReturnForText:text])
        return;
    ++_nativeDepth;
    [super insertText:text];
    if (--_nativeDepth == 0)
        [self flushChanges];
}

- (void)deleteBackward
{
    if (_sink && !_snapshot && !self.markedTextRange)
    {
        [self flushChanges];
        _sink.post(cc::TextInputCommand{cc::TextInputCommandAction::backspace});
        return;
    }
    ++_nativeDepth;
    [super deleteBackward];
    if (--_nativeDepth == 0)
        [self flushChanges];
}

- (void)setMarkedText:(NSString*)text selectedRange:(NSRange)range
{
    ++_nativeDepth;
    [super setMarkedText:text selectedRange:range];
    if (--_nativeDepth == 0)
        [self flushChanges];
}

- (void)unmarkText
{
    ++_nativeDepth;
    [super unmarkText];
    if (--_nativeDepth == 0)
        [self flushChanges];
}

- (void)replaceRange:(UITextRange*)range withText:(NSString*)text
{
    ++_nativeDepth;
    [super replaceRange:range withText:text];
    if (--_nativeDepth == 0)
        [self flushChanges];
}

- (void)textViewDidChange:(UITextView*)textView
{
    [self scheduleFlush];
}

- (void)textViewDidChangeSelection:(UITextView*)textView
{
    [self scheduleFlush];
}

- (void)scheduleFlush
{
    if (!_sink || _programmatic || _nativeDepth || _flushScheduled)
        return;
    _flushScheduled = true;
    const auto session = _sink.session();
    dispatch_async(dispatch_get_main_queue(), ^{
        if (_sink.session() == session)
        {
            _flushScheduled = false;
            [self flushChanges];
        }
    });
}

- (void)observeMark
{
    [self updateMarkedLabel];
    UITextRange* range = self.markedTextRange;
    const bool marked = range != nil;
    const auto composing = marked ? cc::TextInputKnowledge::yes : cc::TextInputKnowledge::no;
    if (_state.composing != composing)
    {
        _state.composing = composing;
        _sink.post(cc::TextInputStateChanged{_state});
    }
    if (_options.observePreedit && (marked || _observedMark))
    {
        cc::TextInputPreedit event;
        if (marked)
        {
            event.phase = _observedMark ? cc::TextInputPreeditPhase::updated : cc::TextInputPreeditPhase::began;
            event.text = utf8String([self textInRange:range]);
            const cc::TextInputIndex index(event.text);
            UITextRange* selected = self.selectedTextRange;
            if (selected)
            {
                const auto start = [self offsetFromPosition:range.start toPosition:selected.start];
                const auto end = [self offsetFromPosition:range.start toPosition:selected.end];
                if (start >= 0 && end >= 0)
                {
                    const auto anchor = index.scalarFromUtf16(start);
                    const auto focus = index.scalarFromUtf16(end);
                    if (anchor && focus)
                        event.selection = cc::TextInputSelection{anchor.offset, focus.offset};
                }
            }
        }
        else
        {
            event.phase = cc::TextInputPreeditPhase::ended;
        }
        _sink.post(std::move(event));
    }
    _observedMark = marked;
}

- (void)flushChanges
{
    if (!_sink || _programmatic || _nativeDepth)
        return;
    [self observeMark];
    if (self.markedTextRange)
        return;

    auto current = utf8String(self.text);
    if (!_snapshot)
    {
        if (!current.empty())
        {
            _sink.post(cc::TextInputCommit{std::move(current)});
            [self installSnapshot];
        }
        return;
    }

    auto& snapshot = *_snapshot;
    const NSRange selected = self.selectedRange;
    const cc::TextInputIndex index(current);
    if (selected.location == NSNotFound || selected.length > (std::numeric_limits<NSUInteger>::max)() - selected.location)
    {
        [self installSnapshot];
        return;
    }
    const auto anchor = index.scalarFromUtf16(selected.location);
    const auto focus = index.scalarFromUtf16(NSMaxRange(selected));
    const auto count = index.scalarCount();
    if (!anchor || !focus || !count || count.offset > (std::numeric_limits<std::size_t>::max)() - snapshot.origin ||
        snapshot.revision == (std::numeric_limits<std::uint64_t>::max)())
    {
        [self installSnapshot];
        return;
    }

    cc::TextInputEdit edit;
    edit.baseRevision = snapshot.revision;
    edit.selectionAfter = {snapshot.origin + anchor.offset, snapshot.origin + focus.offset};
    if (snapshot.anchor == edit.selectionAfter.focus)
        std::swap(edit.selectionAfter.anchor, edit.selectionAfter.focus);

    if (current != snapshot.utf8)
    {
        auto operation = replacement(snapshot, current);
        if (!operation)
        {
            [self installSnapshot];
            return;
        }
        edit.operations.emplace_back(std::move(*operation));
    }
    if (edit.operations.empty() && edit.selectionAfter.anchor == snapshot.anchor && edit.selectionAfter.focus == snapshot.focus)
        return;

    edit.transactionId = _nextTransaction++;
    if (_sink.post(edit, _snapshotEpoch))
    {
        ++snapshot.revision;
        snapshot.utf8 = std::move(current);
        snapshot.anchor = edit.selectionAfter.anchor;
        snapshot.focus = edit.selectionAfter.focus;
        snapshot.acknowledgedTransaction = edit.transactionId;
    }
}

- (void)keyboardChanged:(NSNotification*)notification
{
    if (!_sink || !self.isFirstResponder)
        return;
    if (auto change = cc::iosKeyboardChange((__bridge void*)_host, (__bridge void*)notification, _state))
    {
        _state = change->state;
        _sink.post(std::move(*change));
    }
}
@end

namespace cc
{
namespace
{
class IOSTextInputBackend final : public TextInputBackend
{
public:
    explicit IOSTextInputBackend(CCEAGLView* host) : _view([[CCSessionTextInputView alloc] initWithHost:host]) {}
    ~IOSTextInputBackend() override { [_view finish]; }

    TextInputCapabilities capabilities() const override
    {
        TextInputCapabilities result;
        result.anchor = true;
        result.observePreedit = true;
        result.rangeEdit = true;
        result.keyboardVisibility = true;
        result.keyboardOcclusion = true;
        result.requestKeyboard = true;
        result.cancelComposition = true;
        return result;
    }

    TextInputCapabilities nativeEditingCapabilities() const override
    {
        TextInputCapabilities result;
        result.keyboardVisibility = true;
        result.keyboardOcclusion = true;
        return result;
    }

    TextInputError activate(const TextInputActivation& activation) override
    {
        return [_view start:activation] ? TextInputError::none : TextInputError::activationFailed;
    }

    void setArea(const std::optional<TextInputArea>& area) override { [_view updateArea:area]; }
    void updateSnapshot(const TextInputSnapshot& snapshot) override { [_view updateSnapshot:snapshot]; }

    TextInputError requestKeyboard(bool visible) override
    {
        return [_view requestKeyboard:visible] ? TextInputError::none : TextInputError::activationFailed;
    }

    TextInputError cancelComposition() override
    {
        [_view cancelComposition];
        return TextInputError::none;
    }

    void deactivate() override { [_view finish]; }

private:
    CCSessionTextInputView* _view;
};
}  // namespace

std::unique_ptr<TextInputBackend> createIOSTextInputBackend(void* hostView)
{
    return std::make_unique<IOSTextInputBackend>((__bridge CCEAGLView*)hostView);
}

std::optional<TextInputStateChanged> iosKeyboardChange(void* hostView, void* notification, TextInputState observed)
{
    CCEAGLView* host = (__bridge CCEAGLView*)hostView;
    NSNotification* note = (__bridge NSNotification*)notification;
    UIScreen* screen = host.window.screen;
    if (!screen || ([note.object isKindOfClass:UIScreen.class] && screen != note.object))
        return std::nullopt;
    NSNumber* local = note.userInfo[UIKeyboardIsLocalUserInfoKey];
    if (local && !local.boolValue)
        return std::nullopt;

    NSString* name = note.name;
    const bool will = [name isEqualToString:UIKeyboardWillShowNotification] ||
                      [name isEqualToString:UIKeyboardWillChangeFrameNotification] ||
                      [name isEqualToString:UIKeyboardWillHideNotification];
    const bool hide = [name isEqualToString:UIKeyboardWillHideNotification] ||
                      [name isEqualToString:UIKeyboardDidHideNotification];
    TextInputRect occlusion;
    bool visible = false;
    if (!hide)
    {
        NSValue* value = note.userInfo[UIKeyboardFrameEndUserInfoKey];
        if (!value)
            return std::nullopt;
        const CGRect frame = value.CGRectValue;
        visible = !CGRectIsEmpty(CGRectIntersection(screen.coordinateSpace.bounds, frame));
        if (visible)
        {
            const CGRect inView = [host convertKeyboardRectFromScreen:frame];
            const auto clipped = CGRectIntersection(host.bounds, inView);
            if (!CGRectIsEmpty(clipped))
                occlusion = {clipped.origin.x - host.bounds.origin.x, clipped.origin.y - host.bounds.origin.y,
                             clipped.size.width, clipped.size.height};
        }
    }

    TextInputStateChanged result{observed};
    if (will)
    {
        result.targetOcclusion = occlusion;
        NSNumber* duration = note.userInfo[UIKeyboardAnimationDurationUserInfoKey];
        if (duration)
            result.animationDuration = duration.doubleValue;
    }
    else
    {
        result.state.keyboardVisible = visible ? TextInputKnowledge::yes : TextInputKnowledge::no;
        result.state.occlusion = occlusion;
    }
    return result;
}
}  // namespace cc
#else
namespace cc
{
std::unique_ptr<TextInputBackend> createIOSTextInputBackend(void*) { return {}; }
std::optional<TextInputStateChanged> iosKeyboardChange(void*, void*, TextInputState) { return std::nullopt; }
}  // namespace cc
#endif
