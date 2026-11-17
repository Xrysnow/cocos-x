#include "AppDelegate.h"
#import <UIKit/UIKit.h>
#import "platform/ios/EAGLView-ios.h"

@interface DemoViewController : UIViewController
@end

@implementation DemoViewController
- (void)loadView
{
    self.view = [CCEAGLView viewWithFrame:CGRectZero
                            pixelFormat:(__bridge NSString*)cc::GLViewImpl::_pixelFormat
                            depthFormat:cc::GLViewImpl::_depthFormat
                     preserveBackbuffer:NO sharegroup:nil multiSampling:NO numberOfSamples:0];
    self.view.multipleTouchEnabled = YES;
}
- (BOOL)prefersStatusBarHidden { return YES; }
- (BOOL)prefersHomeIndicatorAutoHidden { return YES; }
@end

@interface DemoAppController : UIResponder <UIApplicationDelegate>
- (BOOL)attachGameWindow:(UIWindow*)window;
- (void)setForeground:(BOOL)foreground forGameWindow:(UIWindow*)window;
- (void)detachGameWindow:(UIWindow*)window;
@end

@implementation DemoAppController
{
    AppDelegate _app;
    // GLViewImpl refers to this view for the lifetime of the Cocos scene.
    // Keep the controller alive while UIKit disconnects its window.
    DemoViewController* _gameController;
    __weak UIWindow* _gameWindow;
    BOOL _started;
    BOOL _foreground;
    BOOL _launchFailed;
}

- (BOOL)application:(UIApplication*)application didFinishLaunchingWithOptions:(NSDictionary*)options
{
    _app.initGLContextAttrs();
    cc::GLViewImpl::convertAttrs();
    return YES;
}

- (BOOL)attachGameWindow:(UIWindow*)window
{
    if (_launchFailed)
        return NO;
    if (_gameWindow)
        return _gameWindow == window;

    if (!_gameController)
        _gameController = [[DemoViewController alloc] init];
    _gameWindow = window;
    window.rootViewController = _gameController;
    [window makeKeyAndVisible];
    _gameController.view.frame = window.bounds;
    const CGFloat scale = window.traitCollection.displayScale;
    if (scale > 0)
        _gameController.view.contentScaleFactor = scale;

    if (_started)
        return YES;

    auto view = cc::GLViewImpl::createWithEAGLView((__bridge void*)_gameController.view);
    if (!view)
    {
        NSLog(@"cocos-x Demo: failed to create the Metal surface");
        _launchFailed = YES;
        [self detachGameWindow:window];
        return NO;
    }
    cc::Director::getInstance()->setOpenGLView(view);
    if (_app.run() != 0)
    {
        NSLog(@"cocos-x Demo: failed to start the game");
        _launchFailed = YES;
        _app.applicationDidEnterBackground();
        [self detachGameWindow:window];
        return NO;
    }
    _started = YES;
    _foreground = YES;
    return YES;
}

- (void)setForeground:(BOOL)foreground forGameWindow:(UIWindow*)window
{
    if (!_started || !window || window != _gameWindow || foreground == _foreground)
        return;
    _foreground = foreground;
    if (foreground)
    {
        _app.applicationWillEnterForeground();
        [_gameController.view setNeedsLayout];
    }
    else
        _app.applicationDidEnterBackground();
}

- (void)detachGameWindow:(UIWindow*)window
{
    if (!window || window != _gameWindow)
        return;
    [self setForeground:NO forGameWindow:window];
    window.hidden = YES;
    window.rootViewController = nil;
    _gameWindow = nil;
}
@end

@interface DemoSceneController : UIResponder <UIWindowSceneDelegate>
@property(nonatomic, strong) UIWindow* window;
@end

@implementation DemoSceneController
- (DemoAppController*)appController
{
    return (DemoAppController*)UIApplication.sharedApplication.delegate;
}

- (void)scene:(UIScene*)scene willConnectToSession:(UISceneSession*)session
      options:(UISceneConnectionOptions*)connectionOptions
{
    if (![scene isKindOfClass:UIWindowScene.class])
        return;
    UIWindow* window = [[UIWindow alloc] initWithWindowScene:(UIWindowScene*)scene];
    if ([[self appController] attachGameWindow:window])
        self.window = window;
}

- (void)sceneWillEnterForeground:(UIScene*)scene
{
    [[self appController] setForeground:YES forGameWindow:self.window];
}

- (void)sceneDidBecomeActive:(UIScene*)scene
{
    [[self appController] setForeground:YES forGameWindow:self.window];
}

- (void)sceneDidEnterBackground:(UIScene*)scene
{
    [[self appController] setForeground:NO forGameWindow:self.window];
}

- (void)sceneDidDisconnect:(UIScene*)scene
{
    [[self appController] detachGameWindow:self.window];
    self.window = nil;
}
@end

int main(int argc, char** argv)
{
    @autoreleasepool
    {
        return UIApplicationMain(argc, argv, nil, NSStringFromClass(DemoAppController.class));
    }
}
