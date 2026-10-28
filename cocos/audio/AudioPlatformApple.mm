/****************************************************************************
 Copyright (c) 2014-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 Copyright (c) 2018-2020 HALX99.
 Copyright (c) 2021-2022 Bytedance Inc.

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
// Audio-session responsibilities migrated from the retired AudioEngineImpl.
#include "AudioPlatform.h"
#include "AudioEngine.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
#import <AVFoundation/AVFoundation.h>
#import <UIKit/UIKit.h>

@interface CCAudioSessionHandler : NSObject
{
    BOOL _enabled;
    BOOL _interrupted;
    BOOL _appActive;
    BOOL _resumeAllowed;
}
- (BOOL)start:(std::string&)error;
- (void)stop;
- (void)handleNotification:(NSNotification*)notification;
- (void)updateState;
@end

@implementation CCAudioSessionHandler
- (BOOL)start:(std::string&)error
{
    NSError* sessionError = nil;
    AVAudioSession* session = [AVAudioSession sharedInstance];
    if (![session setCategory:AVAudioSessionCategoryAmbient error:&sessionError]
        || ![session setActive:YES error:&sessionError])
    {
        error = "Could not activate iOS audio session: ";
        if (sessionError)
            error += [[sessionError localizedDescription] UTF8String];
        return NO;
    }
    _enabled = YES;
    _interrupted = NO;
    _resumeAllowed = YES;
    _appActive = [UIApplication sharedApplication].applicationState == UIApplicationStateActive;
    NSNotificationCenter* center = [NSNotificationCenter defaultCenter];
    [center addObserver:self selector:@selector(handleNotification:)
                   name:AVAudioSessionInterruptionNotification object:session];
    [center addObserver:self selector:@selector(handleNotification:)
                   name:UIApplicationWillResignActiveNotification object:nil];
    [center addObserver:self selector:@selector(handleNotification:)
                   name:UIApplicationDidBecomeActiveNotification object:nil];
    [self updateState];
    return YES;
}

- (void)handleNotification:(NSNotification*)notification
{
    // Engine lifecycle and cocos Ref ownership stay on the main thread.
    if (![NSThread isMainThread])
    {
        dispatch_async(dispatch_get_main_queue(), ^{ [self handleNotification:notification]; });
        return;
    }
    if (!_enabled)
        return;
    if ([notification.name isEqualToString:AVAudioSessionInterruptionNotification])
    {
        NSUInteger type = [notification.userInfo[AVAudioSessionInterruptionTypeKey] unsignedIntegerValue];
        _interrupted = type == AVAudioSessionInterruptionTypeBegan;
        if (!_interrupted)
        {
            NSUInteger options = [notification.userInfo[AVAudioSessionInterruptionOptionKey] unsignedIntegerValue];
            _resumeAllowed = (options & AVAudioSessionInterruptionOptionShouldResume) != 0;
        }
    }
    else if ([notification.name isEqualToString:UIApplicationWillResignActiveNotification])
        _appActive = NO;
    else if ([notification.name isEqualToString:UIApplicationDidBecomeActiveNotification])
    {
        _appActive = YES;
        _resumeAllowed = YES;
    }
    [self updateState];
}

- (void)updateState
{
    BOOL suspended = _interrupted || !_appActive || !_resumeAllowed;
    if (!suspended)
    {
        NSError* error = nil;
        if (![[AVAudioSession sharedInstance] setActive:YES error:&error])
        {
            AERRO("Could not reactivate iOS audio session: %s", [[error localizedDescription] UTF8String]);
            suspended = YES;
        }
    }
    // Source pause/resume and optional OpenAL device suspension share the
    // engine's app/session gate; UIKit events never replace its saved Sources.
    cocos2d::AudioEngine::onAudioSessionInterruption(suspended);
}

- (void)stop
{
    _enabled = NO;
    [[NSNotificationCenter defaultCenter] removeObserver:self];
}

- (void)dealloc
{
    [self stop];
    [super dealloc];
}
@end

NS_CC_BEGIN
namespace AudioInternal
{
    static CCAudioSessionHandler* sessionHandler = nil;

    bool initializeAudioSession(std::string& error)
    {
        if (sessionHandler)
            return true;
        sessionHandler = [[CCAudioSessionHandler alloc] init];
        if (sessionHandler && [sessionHandler start:error])
            return true;
        shutdownAudioSession();
        return false;
    }

    void shutdownAudioSession()
    {
        [sessionHandler stop];
        [sessionHandler release];
        sessionHandler = nil;
    }
}
NS_CC_END
#endif
