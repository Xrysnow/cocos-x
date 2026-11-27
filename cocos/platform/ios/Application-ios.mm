/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org
 Copyright (c) 2013-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

 https://axmolengine.github.io/

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/
#import "Application.h"

#import <AVFAudio/AVAudioSession.h>
#import <UIKit/UIKit.h>

#import "base/Director.h"
#import "haptics/private/MobileHaptics.h"
#import "math/Math.h"
#import "platform/ios/DirectorCaller-ios.h"
#import "platform/GLView.h"
#import "base/ccUtils.h"

@interface CCIOSHapticFocus : NSObject
- (void)startWithGamepadFocus:(void (*)(bool))setGamepadFocus;
- (void)stop;
@end

@implementation CCIOSHapticFocus {
    void (*_setGamepadFocus)(bool);
    NSString* _sceneId;
    BOOL _usesScenes;
    BOOL _observing;
    BOOL _windowActive;
    BOOL _interrupted;
    BOOL _outputActive;
}

- (void)updateOutputFocus
{
    const BOOL active = _windowActive && !_interrupted;
    if (_outputActive != active)
    {
        _outputActive = active;
        cc::haptics::detail::mobileFocus(active);
    }
}

- (void)setWindowActive:(BOOL)active
{
    _windowActive = active;
    _setGamepadFocus(active);
    [self updateOutputFocus];
}

- (void)applicationDidBecomeActive:(NSNotification*)notification
{
    if (!_usesScenes)
        [self setWindowActive:YES];
}

- (void)applicationLostFocus:(NSNotification*)notification
{
    if (!_usesScenes || [notification.name isEqualToString:UIApplicationWillTerminateNotification])
        [self setWindowActive:NO];
}

- (UIScene*)windowScene API_AVAILABLE(ios(13.0))
{
    auto* view = cc::Director::getInstance()->getOpenGLView();
    UIView* host = view ? (__bridge UIView*)view->getEAGLView() : nil;
    return host.window.windowScene;
}

- (void)sceneDidActivate:(NSNotification*)notification API_AVAILABLE(ios(13.0))
{
    UIScene* scene = [self windowScene];
    if (scene && scene == notification.object)
    {
        _usesScenes = YES;
        [_sceneId release];
        _sceneId = [scene.session.persistentIdentifier copy];
        [self setWindowActive:YES];
    }
}

- (void)sceneLostFocus:(NSNotification*)notification API_AVAILABLE(ios(13.0))
{
    UIScene* scene = notification.object;
    UIScene* host = [self windowScene];
    if (scene == host || (!host && [_sceneId isEqualToString:scene.session.persistentIdentifier]))
    {
        [self setWindowActive:NO];
        if ([notification.name isEqualToString:UISceneDidDisconnectNotification])
        {
            [_sceneId release];
            _sceneId = nil;
        }
    }
}

// This notification path also supports SDKs and systems before iOS 27.
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
- (void)audioSessionInterrupted:(NSNotification*)notification
{
    if (![NSThread isMainThread])
    {
        [self performSelectorOnMainThread:_cmd withObject:notification waitUntilDone:NO];
        return;
    }
    if (!_observing)
        return;
    NSNumber* type = notification.userInfo[AVAudioSessionInterruptionTypeKey];
    if (!type)
        return;
    switch (type.unsignedIntegerValue)
    {
    case AVAudioSessionInterruptionTypeBegan: _interrupted = YES; break;
    case AVAudioSessionInterruptionTypeEnded: _interrupted = NO; break;
    default: return;
    }
    [self updateOutputFocus];
}

- (void)startWithGamepadFocus:(void (*)(bool))setGamepadFocus
{
    _setGamepadFocus = setGamepadFocus;
    _observing = YES;
    NSNotificationCenter* center = NSNotificationCenter.defaultCenter;
    [center addObserver:self selector:@selector(audioSessionInterrupted:) name:AVAudioSessionInterruptionNotification object:nil];
    [center addObserver:self selector:@selector(applicationDidBecomeActive:) name:UIApplicationDidBecomeActiveNotification object:nil];
    for (NSString* name in @[UIApplicationWillResignActiveNotification, UIApplicationDidEnterBackgroundNotification,
                             UIApplicationWillTerminateNotification])
        [center addObserver:self selector:@selector(applicationLostFocus:) name:name object:nil];

    if (@available(iOS 13.0, *))
    {
        UIScene* scene = [self windowScene];
        _usesScenes = scene || [NSBundle.mainBundle objectForInfoDictionaryKey:@"UIApplicationSceneManifest"];
        [center addObserver:self selector:@selector(sceneDidActivate:) name:UISceneDidActivateNotification object:nil];
        for (NSString* name in @[UISceneWillDeactivateNotification, UISceneDidEnterBackgroundNotification,
                                 UISceneDidDisconnectNotification])
            [center addObserver:self selector:@selector(sceneLostFocus:) name:name object:nil];
        if (_usesScenes)
        {
            _sceneId = [scene.session.persistentIdentifier copy];
            [self setWindowActive:scene && scene.activationState == UISceneActivationStateForegroundActive];
            return;
        }
    }
    [self setWindowActive:UIApplication.sharedApplication.applicationState == UIApplicationStateActive];
}
#pragma clang diagnostic pop

- (void)stop
{
    _observing = NO;
    [NSNotificationCenter.defaultCenter removeObserver:self];
    _windowActive = NO;
    [self updateOutputFocus];
}

- (void)dealloc
{
    [_sceneId release];
    [super dealloc];
}
@end

NS_CC_BEGIN

Application* Application::sm_pSharedApplication = nullptr;
static CCIOSHapticFocus* s_hapticFocus;

Application::Application()
{
    CC_ASSERT(!sm_pSharedApplication);
    sm_pSharedApplication = this;
}

Application::~Application()
{
    CC_ASSERT(this == sm_pSharedApplication);
    [s_hapticFocus stop];
    [s_hapticFocus release];
    s_hapticFocus = nil;
    sm_pSharedApplication = 0;
}

int Application::run()
{
    if (!s_hapticFocus)
        haptics::detail::mobileFocus(false);
    if (!applicationDidFinishLaunching())
        return 1;
    if (!s_hapticFocus)
    {
        s_hapticFocus = [[CCIOSHapticFocus alloc] init];
        [s_hapticFocus startWithGamepadFocus:[](bool active) {
            auto* director = Director::getInstance();
            if (auto* view = director->getOpenGLView())
                director->setGamepadWindowFocus(view, active);
        }];
    }
    [[CCDirectorCaller sharedDirectorCaller] startMainLoop];
    return 0;
}

void Application::setAnimationInterval(float interval)
{
    [[CCDirectorCaller sharedDirectorCaller] setAnimationInterval:interval];
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// static member function
//////////////////////////////////////////////////////////////////////////////////////////////////

Application* Application::getInstance()
{
    CC_ASSERT(sm_pSharedApplication);
    return sm_pSharedApplication;
}

const char* Application::getCurrentLanguageCode()
{
    static char code[3]       = {0};
    NSUserDefaults* defaults  = [NSUserDefaults standardUserDefaults];
    NSArray* languages        = [defaults objectForKey:@"AppleLanguages"];
    NSString* currentLanguage = [languages objectAtIndex:0];

    // get the current language code.(such as English is "en", Chinese is "zh" and so on)
    NSDictionary* temp     = [NSLocale componentsFromLocaleIdentifier:currentLanguage];
    NSString* languageCode = [temp objectForKey:NSLocaleLanguageCode];
    [languageCode getCString:code maxLength:3 encoding:NSASCIIStringEncoding];
    code[2] = '\0';
    return code;
}

LanguageType Application::getCurrentLanguage()
{
    // get the current language and country config
    NSUserDefaults* defaults  = [NSUserDefaults standardUserDefaults];
    NSArray* languages        = [defaults objectForKey:@"AppleLanguages"];
    NSString* currentLanguage = [languages objectAtIndex:0];

    // get the current language code.(such as English is "en", Chinese is "zh" and so on)
    NSDictionary* temp     = [NSLocale componentsFromLocaleIdentifier:currentLanguage];
    NSString* languageCode = [temp objectForKey:NSLocaleLanguageCode];

    return utils::getLanguageTypeByISO2([languageCode UTF8String]);
}

Application::Platform Application::getTargetPlatform()
{
    return Platform::iOS;
}

std::string Application::getVersion()
{
    NSString* version = [[[NSBundle mainBundle] infoDictionary] objectForKey:@"CFBundleShortVersionString"];
    if (version)
    {
        return [version UTF8String];
    }
    return "";
}

bool Application::openURL(std::string_view url)
{
    NSString* msg = [NSString stringWithCString:url.data() encoding:NSUTF8StringEncoding];
    NSURL* nsUrl  = [NSURL URLWithString:msg];

    id application = [UIApplication sharedApplication];
    if ([application respondsToSelector:@selector(openURL:options:completionHandler:)])
    {
        [application openURL:nsUrl options:@{} completionHandler:nil];
    }
    else
    {
        return [application openURL:nsUrl];
    }
}

void Application::applicationScreenSizeChanged(int newWidth, int newHeight) {}

NS_CC_END
