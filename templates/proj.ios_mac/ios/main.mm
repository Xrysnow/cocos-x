#include "AppDelegate.h"
#import <UIKit/UIKit.h>
#import "platform/ios/EAGLView-ios.h"

@interface DemoViewController : UIViewController
@end

@implementation DemoViewController
- (void)loadView
{
    self.view = [CCEAGLView viewWithFrame:UIScreen.mainScreen.bounds
                            pixelFormat:(__bridge NSString*)cc::GLViewImpl::_pixelFormat
                            depthFormat:cc::GLViewImpl::_depthFormat
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
    cc::GLViewImpl::convertAttrs();
    self.window = [[UIWindow alloc] initWithFrame:UIScreen.mainScreen.bounds];
    self.window.rootViewController = [[DemoViewController alloc] init];
    [self.window makeKeyAndVisible];
    auto view = cc::GLViewImpl::createWithEAGLView((__bridge void*)self.window.rootViewController.view);
    if (!view)
        return NO;
    cc::Director::getInstance()->setOpenGLView(view);
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
