#import <UIKit/UIKit.h>

#include "platform/apple/FileDialog-apple.h"
#include "platform/GLView.h"

#include <chrono>

using namespace cc;
using namespace cc::dialog;

// Keep the delegate, stage and service callback alive until the native UI has exited.
@interface CocosDocumentPickerSession : NSObject <UIDocumentPickerDelegate, UIAdaptivePresentationControllerDelegate>
{
@public
    NativeRequest request;
    NativeCallback callback;
    __weak UIView* parentView;
    __weak UIWindowScene* scene;
    __weak UIViewController* presenter;
    UIDocumentPickerViewController* picker;
    id sceneObserver;
    std::optional<NativeResult> result;
    std::chrono::steady_clock::time_point presentationDeadline;
    bool seenPresentation;
    bool dismissRequested;
    bool validateExtensions;
}
- (void)finish;
- (void)closeWithResult:(NativeResult)terminal;
- (void)updatePresentation;
@end

namespace
{
CocosDocumentPickerSession* active = nil;

NativeResult cancelled()
{
    NativeResult terminal;
    terminal.status = DialogStatus::Cancelled;
    terminal.cancelReason = CancelReason::User;
    return terminal;
}

NativeResult failed(DialogErrorCode code, const char* text, ExternalEffect effect = ExternalEffect::None)
{
    NativeResult terminal;
    terminal.error = {code, text};
    terminal.effect = effect;
    return terminal;
}

void observePresentation(CocosDocumentPickerSession* session)
{
    // UIKit can remove a picker with its presenter, without calling either delegate.
    __weak CocosDocumentPickerSession* weakSession = session;
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, 150 * NSEC_PER_MSEC), dispatch_get_main_queue(), ^{
        CocosDocumentPickerSession* current = weakSession;
        if (!current || active != current)
            return;
        if (!current->parentView.window || current->parentView.window.windowScene != current->scene)
        {
            const bool exporting = current->request.operation == Operation::Export;
            [current closeWithResult:failed(DialogErrorCode::ParentClosed, "The document picker's scene closed",
                                            exporting ? ExternalEffect::Unknown : ExternalEffect::None)];
        }
        [current updatePresentation];
        // During a host-driven dismissal UIKit may invoke neither delegate.
        // Keep watching even after a terminal result has been recorded.
        if (active == current)
            observePresentation(current);
    });
}

void present(UIView* owner, NativeRequest request, NativeCallback callback)
{
    UIWindow* window = owner.window;
    UIWindowScene* scene = window.windowScene;
    UIViewController* presenter = window.rootViewController;
    while (presenter.presentedViewController && !presenter.presentedViewController.isBeingDismissed)
        presenter = presenter.presentedViewController;
    if (active)
    {
        callback(failed(DialogErrorCode::Busy, "The UIKit document picker is already visible"));
        return;
    }
    if (!scene || scene.activationState != UISceneActivationStateForegroundActive || window.hidden ||
        presenter.viewIfLoaded.window != window || !presenter || presenter.presentedViewController ||
        presenter.isBeingPresented || presenter.isBeingDismissed || presenter.transitionCoordinator)
    {
        callback(failed(DialogErrorCode::Unavailable, "The engine view needs an active scene and an available presenter"));
        return;
    }

    UIDocumentPickerViewController* picker = nil;
    const bool exporting = request.operation == Operation::Export;
    const auto types = apple::contentTypes(request.options);
    if (exporting)
    {
        if (!request.stagingPath.empty())
        {
            auto* source = [NSURL fileURLWithFileSystemRepresentation:request.stagingPath.c_str()
                                                        isDirectory:NO relativeToURL:nil];
            picker = [[UIDocumentPickerViewController alloc] initForExportingURLs:@[source] asCopy:YES];
        }
    }
    else if (request.operation == Operation::Open || request.operation == Operation::Folder)
    {
        const bool folder = request.operation == Operation::Folder;
        NSArray<UTType*>* allowed = folder ? @[UTTypeFolder] : (types.types.count ? types.types : @[UTTypeData]);
        picker = [[UIDocumentPickerViewController alloc] initForOpeningContentTypes:allowed asCopy:NO];
        picker.allowsMultipleSelection = !folder && request.options.allowMultiple;
    }
    if (!picker)
    {
        callback(failed(request.operation == Operation::SaveTarget ? DialogErrorCode::UnsupportedFeature :
                        DialogErrorCode::Unavailable, "UIKit could not initialize the requested document picker"));
        return;
    }
    if (NSURL* directory = apple::directoryURL(request.options.initialDirectory))
        picker.directoryURL = directory;
    if (!request.options.title.empty())
        picker.title = apple::string(request.options.title);
    picker.popoverPresentationController.sourceView = presenter.view;
    picker.popoverPresentationController.sourceRect = CGRectMake(CGRectGetMidX(presenter.view.bounds),
                                                                 CGRectGetMidY(presenter.view.bounds), 1, 1);

    if (exporting && (!request.beginExternalWrite || !request.beginExternalWrite()))
    {
        callback(cancelled());
        return;
    }

    CocosDocumentPickerSession* session = [CocosDocumentPickerSession new];
    session->request = std::move(request);
    session->callback = std::move(callback);
    session->parentView = owner;
    session->scene = scene;
    session->presenter = presenter;
    session->picker = picker;
    session->presentationDeadline = std::chrono::steady_clock::now() + std::chrono::seconds(5);
    session->validateExtensions = types.needsExtensionCheck;
    active = session;
    picker.delegate = session;
    picker.presentationController.delegate = session;
    __weak CocosDocumentPickerSession* weakSession = session;
    session->sceneObserver = [[NSNotificationCenter defaultCenter] addObserverForName:UISceneDidDisconnectNotification
        object:scene queue:nil usingBlock:^(NSNotification*) {
            CocosDocumentPickerSession* current = weakSession;
            [current closeWithResult:failed(DialogErrorCode::ParentClosed, "The document picker's scene disconnected",
                                            exporting ? ExternalEffect::Unknown : ExternalEffect::None)];
        }];
    [presenter presentViewController:picker animated:YES completion:^{
        CocosDocumentPickerSession* current = weakSession;
        if (current && active == current)
        {
            current->seenPresentation = true;
            [current updatePresentation];
        }
    }];
    picker.presentationController.delegate = session;
    observePresentation(session);
}
}

@implementation CocosDocumentPickerSession
- (void)finish
{
    if (active != self || !result)
        return;
    CocosDocumentPickerSession* keepAlive __attribute__((objc_precise_lifetime)) = self;
    active = nil;
    [[NSNotificationCenter defaultCenter] removeObserver:sceneObserver];
    sceneObserver = nil;
    picker.delegate = nil;
    picker.presentationController.delegate = nil;
    picker = nil;
    auto completion = std::move(callback);
    completion(std::move(*result));
    (void)keepAlive;
}

- (void)closeWithResult:(NativeResult)terminal
{
    if (active != self || result)
        return;
    result = std::move(terminal);
    [self updatePresentation];
}

- (void)updatePresentation
{
    if (active != self)
        return;
    const bool attached = picker.presentingViewController || presenter.presentedViewController == picker ||
                          picker.viewIfLoaded.window;
    if (attached)
    {
        seenPresentation = true;
        if (result && !dismissRequested && !picker.isBeingPresented && !picker.isBeingDismissed)
        {
            dismissRequested = true;
            __weak CocosDocumentPickerSession* weakSelf = self;
            [picker dismissViewControllerAnimated:YES completion:^{ [weakSelf finish]; }];
        }
        return;
    }
    // UIKit can establish the presenting relationship asynchronously.
    if (picker.isBeingPresented || (!seenPresentation && std::chrono::steady_clock::now() < presentationDeadline))
        return;
    if (!result)
    {
        const auto effect = request.operation == Operation::Export ? ExternalEffect::Unknown : ExternalEffect::None;
        result = seenPresentation ? failed(DialogErrorCode::ParentClosed, "The document picker was detached", effect)
                                  : failed(DialogErrorCode::Unavailable, "UIKit refused to present the document picker", effect);
    }
    [self finish];
}

- (void)documentPicker:(UIDocumentPickerViewController*)controller didPickDocumentsAtURLs:(NSArray<NSURL*>*)urls
{
    if (controller != picker || result)
        return;
    seenPresentation = true;
    NativeResult terminal;
    if (request.operation == Operation::Export)
    {
        NSURL* destination = urls.firstObject;
        if (urls.count != 1 || !destination.isFileURL)
            terminal = failed(DialogErrorCode::InvalidResult, "UIKit returned no valid export destination", ExternalEffect::Unknown);
        else
        {
            terminal.status = DialogStatus::Ok;
            terminal.effect = ExternalEffect::Committed;
            // The Files provider can report the containing directory after an export.
            if (!destination.hasDirectoryPath)
                terminal.displayName = apple::string(destination.lastPathComponent);
        }
    }
    else
        terminal = apple::selection(urls, request, validateExtensions);
    [self closeWithResult:std::move(terminal)];
}

- (void)documentPickerWasCancelled:(UIDocumentPickerViewController*)controller
{
    if (controller == picker)
    {
        seenPresentation = true;
        [self closeWithResult:cancelled()];
    }
}

- (void)presentationControllerDidDismiss:(UIPresentationController*)presentationController
{
    if (presentationController.presentedViewController != picker)
        return;
    if (!result)
    {
        result = cancelled();
        if (request.operation == Operation::Export)
            result->effect = ExternalEffect::Unknown;
    }
    [self finish];
}
@end

namespace cc::dialog
{
DialogCapabilities nativeCapabilities()
{
    DialogCapabilities capabilities;
    capabilities.backend = "UIKit";
    capabilities.available = capabilities.openFiles = capabilities.multipleFiles = capabilities.pickFolder =
        capabilities.exportFile = capabilities.initialDirectoryHint = capabilities.physicalDismiss = true;
    return capabilities;
}

void presentNative(NativeRequest request, NativeCallback callback)
{
    __weak UIView* owner = request.view ? (__bridge UIView*)request.view->getEAGLView() : nil;
    request.view = nullptr;
    if ([NSThread isMainThread])
        present(owner, std::move(request), std::move(callback));
    else
        dispatch_async(dispatch_get_main_queue(), ^{ present(owner, request, callback); });
}

void cancelNative(uint64_t id)
{
    dispatch_async(dispatch_get_main_queue(), ^{
        if (active && active->request.id == id && active->request.operation != Operation::Export)
            [active closeWithResult:cancelled()];
    });
}

void shutdownNative()
{
    apple::stopCoordinating();
    dispatch_async(dispatch_get_main_queue(), ^{
        // A system-owned copy must retain staging until UIKit releases the picker.
        if (active && active->request.operation != Operation::Export)
            [active closeWithResult:cancelled()];
    });
}
}
