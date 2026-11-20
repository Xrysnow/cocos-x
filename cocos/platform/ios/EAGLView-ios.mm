/*

===== IMPORTANT =====

This is sample code demonstrating API, technology or techniques in development.
Although this sample code has been reviewed for technical accuracy, it is not
final. Apple is supplying this information to help you plan for the adoption of
the technologies and programming interfaces described herein. This information
is subject to change, and software implemented based on this sample code should
be tested with final operating system software and final documentation. Newer
versions of this sample code may be provided with future seeds of the API or
technology. For information about updates to this and other developer
documentation, view the New & Updated sidebars in subsequent documentation
seeds.

=====================

File: EAGLView.m
Abstract: Convenience class that wraps the CAEAGLLayer from CoreAnimation into a
UIView subclass.

Version: 1.3

Disclaimer: IMPORTANT:  This Apple software is supplied to you by Apple Inc.
("Apple") in consideration of your agreement to the following terms, and your
use, installation, modification or redistribution of this Apple software
constitutes acceptance of these terms.  If you do not agree with these terms,
please do not use, install, modify or redistribute this Apple software.

In consideration of your agreement to abide by the following terms, and subject
to these terms, Apple grants you a personal, non-exclusive license, under
Apple's copyrights in this original Apple software (the "Apple Software"), to
use, reproduce, modify and redistribute the Apple Software, with or without
modifications, in source and/or binary forms; provided that if you redistribute
the Apple Software in its entirety and without modifications, you must retain
this notice and the following text and disclaimers in all such redistributions
of the Apple Software.
Neither the name, trademarks, service marks or logos of Apple Inc. may be used
to endorse or promote products derived from the Apple Software without specific
prior written permission from Apple.  Except as expressly stated in this notice,
no other rights or licenses, express or implied, are granted by Apple herein,
including but not limited to any patent rights that may be infringed by your
derivative works or by other works in which the Apple Software may be
incorporated.

The Apple Software is provided by Apple on an "AS IS" basis.  APPLE MAKES NO
WARRANTIES, EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION THE IMPLIED
WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY AND FITNESS FOR A PARTICULAR
PURPOSE, REGARDING THE APPLE SOFTWARE OR ITS USE AND OPERATION ALONE OR IN
COMBINATION WITH YOUR PRODUCTS.

IN NO EVENT SHALL APPLE BE LIABLE FOR ANY SPECIAL, INDIRECT, INCIDENTAL OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
ARISING IN ANY WAY OUT OF THE USE, REPRODUCTION, MODIFICATION AND/OR
DISTRIBUTION OF THE APPLE SOFTWARE, HOWEVER CAUSED AND WHETHER UNDER THEORY OF
CONTRACT, TORT (INCLUDING NEGLIGENCE), STRICT LIABILITY OR OTHERWISE, EVEN IF
APPLE HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

Copyright (C) 2008 Apple Inc. All Rights Reserved.

*/
#import "platform/ios/EAGLView-ios.h"

#import <QuartzCore/QuartzCore.h>

#import "base/Director.h"
#import "base/Touch.h"
#import "platform/TextInputBackend.h"
#import "platform/ios/GLViewImpl-ios.h"
#import "platform/ios/TextInput-ios.h"
#import "renderer/backend/gfx/DeviceGFX.h"

// CLASS IMPLEMENTATIONS:

#define IOS_MAX_TOUCHES_COUNT 10

@interface CCEAGLView ()
@property(nonatomic, readwrite, assign) BOOL isKeyboardShown;
@property(nonatomic, copy) NSNotification* keyboardShowNotification;
- (void)onUIKeyboardNotification:(NSNotification*)notification;
- (void)setKeyboardOffset:(CGFloat)offset;
@end

@implementation CCEAGLView
{
    cc::TextInputState _observedKeyboard;
    CGFloat _keyboardOffset;
}

@synthesize surfaceSize = size_;
@synthesize pixelFormat = pixelformat_, depthFormat = depthFormat_;
@synthesize multiSampling            = multiSampling_;
@synthesize keyboardShowNotification = keyboardShowNotification_;
@synthesize isKeyboardShown;

+ (Class)layerClass
{
    return [CAMetalLayer class];
}

+ (id)viewWithFrame:(CGRect)frame
{
    return [[[self alloc] initWithFrame:frame] autorelease];
}

+ (id)viewWithFrame:(CGRect)frame pixelFormat:(NSString*)format
{
    return [[[self alloc] initWithFrame:frame pixelFormat:format] autorelease];
}

+ (id)viewWithFrame:(CGRect)frame pixelFormat:(NSString*)format depthFormat:(GLuint)depth
{
    return [[[self alloc] initWithFrame:frame
                            pixelFormat:format
                            depthFormat:depth
                     preserveBackbuffer:NO
                             sharegroup:nil
                          multiSampling:NO
                        numberOfSamples:0] autorelease];
}

+ (id)viewWithFrame:(CGRect)frame
           pixelFormat:(NSString*)format
           depthFormat:(GLuint)depth
    preserveBackbuffer:(BOOL)retained
            sharegroup:(EAGLSharegroup*)sharegroup
         multiSampling:(BOOL)multisampling
       numberOfSamples:(unsigned int)samples
{
    return [[[self alloc] initWithFrame:frame
                            pixelFormat:format
                            depthFormat:depth
                     preserveBackbuffer:retained
                             sharegroup:sharegroup
                          multiSampling:multisampling
                        numberOfSamples:samples] autorelease];
}

- (id)initWithFrame:(CGRect)frame
{
    return [self initWithFrame:frame
                   pixelFormat:kEAGLColorFormatRGB565
                   depthFormat:0
            preserveBackbuffer:NO
                    sharegroup:nil
                 multiSampling:NO
               numberOfSamples:0];
}

- (id)initWithFrame:(CGRect)frame pixelFormat:(NSString*)format
{
    return [self initWithFrame:frame
                   pixelFormat:format
                   depthFormat:0
            preserveBackbuffer:NO
                    sharegroup:nil
                 multiSampling:NO
               numberOfSamples:0];
}

- (id)initWithFrame:(CGRect)frame
           pixelFormat:(NSString*)format
           depthFormat:(GLuint)depth
    preserveBackbuffer:(BOOL)retained
            sharegroup:(EAGLSharegroup*)sharegroup
         multiSampling:(BOOL)sampling
       numberOfSamples:(unsigned int)nSamples
{
    if ((self = [super initWithFrame:frame]))
    {
        if ([self respondsToSelector:@selector(setContentScaleFactor:)])
        {
            self.contentScaleFactor = [[UIScreen mainScreen] scale];
        }

        // The backing CAMetalLayer stays unconfigured here. The gfx Metal swapchain
        // validates and owns the layer (device, pixel format, framebufferOnly and
        // drawable size) when the renderer creates the surface; configuring it with a
        // different MTLDevice here would make that adoption fail.
    }

    return self;
}

- (id)initWithCoder:(NSCoder*)aDecoder
{
    if ((self = [super initWithCoder:aDecoder]))
    {
        size_ = [self bounds].size;
    }

    return self;
}

- (int)getWidth
{
    CGSize bound = [self bounds].size;
    return (int)bound.width * self.contentScaleFactor;
}

- (int)getHeight
{
    CGSize bound = [self bounds].size;
    return (int)bound.height * self.contentScaleFactor;
}

- (void)dealloc
{
    [[NSNotificationCenter defaultCenter] removeObserver:self];  // remove keyboard notification
    [keyboardShowNotification_ release];
    [super dealloc];
}

- (void)layoutSubviews
{
    // Touching Director constructs it, but the renderer's DeviceGFX asserts unless
    // GLViewImpl has created the gfx device first (before setOpenGLView).
    if (!cc::backend::DeviceGFX::isAvailable())
        return;

    auto director = cc::Director::getInstance();
    if (!director->isValid())
        return;

    size_ = [self bounds].size;
    size_.width *= self.contentScaleFactor;
    size_.height *= self.contentScaleFactor;

    auto glview = director->getOpenGLView();
    if (glview)
    {
        // Feed the real pixel size to GLViewImpl; it updates the frame size and
        // notifies the gfx renderer, which resizes its swapchain at beginFrame.
        static_cast<cc::GLViewImpl*>(glview)->updateLayoutSize(size_.width, size_.height);
    }

    // Avoid flicker. Issue #350
    if (glview && [NSThread isMainThread])
    {
        director->drawScene();
    }
}

#pragma mark CCEAGLView - Point conversion

- (CGPoint)convertPointFromViewToSurface:(CGPoint)point
{
    CGRect bounds = [self bounds];

    CGPoint ret;
    ret.x = (point.x - bounds.origin.x) / bounds.size.width * size_.width;
    ret.y = (point.y - bounds.origin.y) / bounds.size.height * size_.height;

    return ret;
}

- (CGRect)convertRectFromViewToSurface:(CGRect)rect
{
    CGRect bounds = [self bounds];

    CGRect ret;
    ret.origin.x    = (rect.origin.x - bounds.origin.x) / bounds.size.width * size_.width;
    ret.origin.y    = (rect.origin.y - bounds.origin.y) / bounds.size.height * size_.height;
    ret.size.width  = rect.size.width / bounds.size.width * size_.width;
    ret.size.height = rect.size.height / bounds.size.height * size_.height;

    return ret;
}

// Pass the touches to the superview
#pragma mark CCEAGLView - Touch Delegate
- (void)touchesBegan:(NSSet*)touches withEvent:(UIEvent*)event
{
    const auto view = cc::Director::getInstance()->getOpenGLView();
    if (self.isKeyboardShown && view && view->getTextInputService().focus().native)
        [self closeKeyboardOpenedByEditBox];

    UITouch* ids[IOS_MAX_TOUCHES_COUNT] = {0};
    float xs[IOS_MAX_TOUCHES_COUNT]     = {0.0f};
    float ys[IOS_MAX_TOUCHES_COUNT]     = {0.0f};

    int i = 0;
    for (UITouch* touch in touches)
    {
        if (i >= IOS_MAX_TOUCHES_COUNT)
        {
            CCLOG("warning: touches more than 10, should adjust IOS_MAX_TOUCHES_COUNT");
            break;
        }

        ids[i] = touch;
        xs[i]  = [touch locationInView:[touch view]].x * self.contentScaleFactor;
        ys[i]  = [touch locationInView:[touch view]].y * self.contentScaleFactor;
        ++i;
    }

    auto glView = cc::Director::getInstance()->getOpenGLView();
    glView->handleTouchesBegin(i, (intptr_t*)ids, xs, ys);
}

- (void)touchesMoved:(NSSet*)touches withEvent:(UIEvent*)event
{
    UITouch* ids[IOS_MAX_TOUCHES_COUNT] = {0};
    float xs[IOS_MAX_TOUCHES_COUNT]     = {0.0f};
    float ys[IOS_MAX_TOUCHES_COUNT]     = {0.0f};
    float fs[IOS_MAX_TOUCHES_COUNT]     = {0.0f};
    float ms[IOS_MAX_TOUCHES_COUNT]     = {0.0f};

    int i = 0;
    for (UITouch* touch in touches)
    {
        if (i >= IOS_MAX_TOUCHES_COUNT)
        {
            CCLOG("warning: touches more than 10, should adjust IOS_MAX_TOUCHES_COUNT");
            break;
        }

        ids[i] = touch;
        xs[i]  = [touch locationInView:[touch view]].x * self.contentScaleFactor;
        ys[i]  = [touch locationInView:[touch view]].y * self.contentScaleFactor;
#if defined(__IPHONE_9_0) && (__IPHONE_OS_VERSION_MAX_ALLOWED >= __IPHONE_9_0)
        // running on iOS 9.0 or higher version
        if ([[[UIDevice currentDevice] systemVersion] floatValue] >= 9.0f)
        {
            fs[i] = touch.force;
            ms[i] = touch.maximumPossibleForce;
        }
#endif
        ++i;
    }

    auto glView = cc::Director::getInstance()->getOpenGLView();
    glView->handleTouchesMove(i, (intptr_t*)ids, xs, ys, fs, ms);
}

- (void)touchesEnded:(NSSet*)touches withEvent:(UIEvent*)event
{
    UITouch* ids[IOS_MAX_TOUCHES_COUNT] = {0};
    float xs[IOS_MAX_TOUCHES_COUNT]     = {0.0f};
    float ys[IOS_MAX_TOUCHES_COUNT]     = {0.0f};

    int i = 0;
    for (UITouch* touch in touches)
    {
        if (i >= IOS_MAX_TOUCHES_COUNT)
        {
            CCLOG("warning: touches more than 10, should adjust IOS_MAX_TOUCHES_COUNT");
            break;
        }

        ids[i] = touch;
        xs[i]  = [touch locationInView:[touch view]].x * self.contentScaleFactor;
        ys[i]  = [touch locationInView:[touch view]].y * self.contentScaleFactor;
        ++i;
    }

    auto glView = cc::Director::getInstance()->getOpenGLView();
    glView->handleTouchesEnd(i, (intptr_t*)ids, xs, ys);
}

- (void)touchesCancelled:(NSSet*)touches withEvent:(UIEvent*)event
{
    UITouch* ids[IOS_MAX_TOUCHES_COUNT] = {0};
    float xs[IOS_MAX_TOUCHES_COUNT]     = {0.0f};
    float ys[IOS_MAX_TOUCHES_COUNT]     = {0.0f};

    int i = 0;
    for (UITouch* touch in touches)
    {
        if (i >= IOS_MAX_TOUCHES_COUNT)
        {
            CCLOG("warning: touches more than 10, should adjust IOS_MAX_TOUCHES_COUNT");
            break;
        }

        ids[i] = touch;
        xs[i]  = [touch locationInView:[touch view]].x * self.contentScaleFactor;
        ys[i]  = [touch locationInView:[touch view]].y * self.contentScaleFactor;
        ++i;
    }

    auto glView = cc::Director::getInstance()->getOpenGLView();
    glView->handleTouchesCancel(i, (intptr_t*)ids, xs, ys);
}

- (void)doAnimationWhenKeyboardMoveWithDuration:(float)duration distance:(float)dis
{
    [UIView beginAnimations:nil context:nullptr];
    [UIView setAnimationDelegate:self];
    [UIView setAnimationDuration:duration];
    [UIView setAnimationBeginsFromCurrentState:YES];

    // NSLog(@"[animation] dis = %f, scale = %f \n", dis, cc::GLView::getInstance()->getScaleY());

    if (dis < 0.0f)
        dis = 0.0f;

    auto glView = cc::Director::getInstance()->getOpenGLView();
    dis *= glView->getScaleY();

    dis /= self.contentScaleFactor;

    [self setKeyboardOffset:dis];
    [UIView commitAnimations];
}

- (void)setKeyboardOffset:(CGFloat)offset
{
    // Keep the host's current geometry through rotation and safe-area changes.
    auto transform = self.transform;
    transform.ty += _keyboardOffset - offset;
    self.transform = transform;
    _keyboardOffset = offset;
}

- (CGRect)convertKeyboardRectFromScreen:(CGRect)rect
{
    CGRect local = [self convertRect:rect fromCoordinateSpace:self.window.screen.coordinateSpace];
    if (_keyboardOffset && self.superview)
    {
        // Transform the parent's translation vector into the view's axes before undoing it.
        const CGPoint origin = [self convertPoint:CGPointZero fromView:self.superview];
        const CGPoint offset = [self convertPoint:CGPointMake(0, _keyboardOffset) fromView:self.superview];
        local = CGRectOffset(local, origin.x - offset.x, origin.y - offset.y);
    }
    return local;
}

- (void)doAnimationWhenAnotherEditBeClicked
{
    if (self.keyboardShowNotification != nil)
        [self onUIKeyboardNotification:self.keyboardShowNotification];
}

#pragma UIKeyboard notification

- (void)didMoveToWindow
{
    [super didMoveToWindow];
#if !TARGET_OS_TV
    NSNotificationCenter* center = NSNotificationCenter.defaultCenter;
    for (NSString* name in @[UIKeyboardWillShowNotification, UIKeyboardWillChangeFrameNotification,
                             UIKeyboardWillHideNotification, UIKeyboardDidShowNotification,
                             UIKeyboardDidChangeFrameNotification, UIKeyboardDidHideNotification])
    {
        [center removeObserver:self name:name object:nil];
        if (self.window)
            [center addObserver:self selector:@selector(onUIKeyboardNotification:) name:name object:nil];
    }
    if (!self.window)
    {
        _observedKeyboard = {};
        self.isKeyboardShown = NO;
        self.keyboardShowNotification = nil;
        [self setKeyboardOffset:0];
    }
#endif
}

- (void)onUIKeyboardNotification:(NSNotification*)notif
{
#if !TARGET_OS_TV
    auto change = cc::iosKeyboardChange((void*)self, (void*)notif, _observedKeyboard);
    if (!change)
        return;
    _observedKeyboard = change->state;
    if (!change->targetOcclusion)
    {
        self.isKeyboardShown = _observedKeyboard.keyboardVisible == cc::TextInputKnowledge::yes;
        self.keyboardShowNotification = self.isKeyboardShown ? notif : nil;
    }
    if (!cc::backend::DeviceGFX::isAvailable())
        return;
    const auto view = cc::Director::getInstance()->getOpenGLView();
    if (!view || view->getEAGLView() != self)
        return;
    auto& service = view->getTextInputService();
    const auto focus = service.focus();
    if (!focus.native)
        return;
    const auto sink = service.sinkForWindow(focus.window, true);
    if (sink.session() == focus.session)
        sink.post(std::move(*change));
#endif
}

// Close the keyboard opened by EditBox
- (void)closeKeyboardOpenedByEditBox
{
    NSArray* subviews = self.subviews;

    for (UIView* view in subviews)
    {
        if ([view isKindOfClass:NSClassFromString(@"UITextView")] ||
            [view isKindOfClass:NSClassFromString(@"UITextField")])
        {
            if ([view isFirstResponder])
            {
                [view resignFirstResponder];
                return;
            }
        }
    }
}

@end
