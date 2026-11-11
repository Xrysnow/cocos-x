#include "AppDelegate.h"
#import <UIKit/UIKit.h>
#import "platform/ios/CCEAGLView-ios.h"

@interface DemoViewController : UIViewController
@end

@implementation DemoViewController
- (void)loadView
{
    self.view = [CCEAGLView viewWithFrame:UIScreen.mainScreen.bounds
                            pixelFormat:(__bridge NSString*)cocos2d::GLViewImpl::_pixelFormat
                            depthFormat:cocos2d::GLViewImpl::_depthFormat
                     preserveBackbuffer:NO sharegroup:nil multiSampling:NO numberOfSamples:0];
    self.view.multipleTouchEnabled = YES;
}
- (BOOL)prefersStatusBarHidden { return YES; }
- (BOOL)prefersHomeIndicatorAutoHidden { return YES; }
@end

@interface DemoAppController : UIResponder <UIApplicationDelegate>
{
    AppDelegate _app;
}
@property(nonatomic, strong) UIWindow* window;
@end

@implementation DemoAppController
- (BOOL)application:(UIApplication*)application didFinishLaunchingWithOptions:(NSDictionary*)options
{
    _app.initGLContextAttrs();
    cocos2d::GLViewImpl::convertAttrs();
    self.window = [[UIWindow alloc] initWithFrame:UIScreen.mainScreen.bounds];
    self.window.rootViewController = [[DemoViewController alloc] init];
    [self.window makeKeyAndVisible];
    auto* view = cocos2d::GLViewImpl::createWithEAGLView((__bridge void*)self.window.rootViewController.view);
    if (!view)
        return NO;
    cocos2d::Director::getInstance()->setOpenGLView(view);
    _app.run();
    return YES;
}
- (void)applicationDidEnterBackground:(UIApplication*)application
{
    _app.applicationDidEnterBackground();
}
- (void)applicationWillEnterForeground:(UIApplication*)application
{
    _app.applicationWillEnterForeground();
}
@end

int main(int argc, char** argv)
{
    @autoreleasepool
    {
        return UIApplicationMain(argc, argv, nil, NSStringFromClass(DemoAppController.class));
    }
}
