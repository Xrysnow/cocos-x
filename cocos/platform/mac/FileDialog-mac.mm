#import <AppKit/AppKit.h>

#include "platform/apple/FileDialog-apple.h"
#include "platform/GLView.h"

namespace cc::dialog
{
namespace
{
struct Presentation
{
    NativeRequest request;
    NativeCallback callback;
    NSSavePanel* panel = nil;
    __weak NSWindow* owner = nil;
    id closeObserver = nil;
    bool ownerClosed = false;
    bool validateExtensions = false;
};

// The callback, panel and observer are installed and released on AppKit's thread.
std::unique_ptr<Presentation> active;

void restoreFocus(const Presentation& presentation)
{
    if (presentation.ownerClosed)
        return;
    __weak NSWindow* owner = presentation.owner;
    __weak NSSavePanel* sheet = presentation.panel;
    // Allow AppKit to detach the sheet before selecting a key window. GLFW's
    // Cocoa event pump services the main run loop even without -[NSApp run].
    CFRunLoopPerformBlock(CFRunLoopGetMain(), kCFRunLoopCommonModes, ^{
        NSWindow* window = owner;
        NSWindow* key = NSApp.keyWindow;
        if (NSApp.active && window.visible && !window.miniaturized && window.canBecomeKeyWindow &&
            !window.attachedSheet && (!key || key == sheet))
            [window makeKeyWindow];
    });
    CFRunLoopWakeUp(CFRunLoopGetMain());
}

void complete(uint64_t id, NSModalResponse response)
{
    if (!active || active->request.id != id)
        return;
    auto presentation = std::move(active);
    if (presentation->closeObserver)
        [[NSNotificationCenter defaultCenter] removeObserver:presentation->closeObserver];

    NativeResult result;
    if (presentation->ownerClosed)
        result.error = {DialogErrorCode::ParentClosed, "The file dialog's window closed"};
    else if (response == NSModalResponseCancel)
    {
        result.status = DialogStatus::Cancelled;
        result.cancelReason = CancelReason::User;
    }
    else if (response == NSModalResponseOK)
    {
        if (presentation->request.operation == Operation::Open || presentation->request.operation == Operation::Folder)
            result = apple::selection(static_cast<NSOpenPanel*>(presentation->panel).URLs,
                                      presentation->request, presentation->validateExtensions);
        else if (result.target = apple::saveLocation(presentation->panel.URL, result.error); result.target)
            result.status = DialogStatus::Ok;
    }
    else
        result.error = {DialogErrorCode::BackendError, "AppKit ended the file dialog unexpectedly"};
    restoreFocus(*presentation);
    presentation->callback(std::move(result));
}

void present(NSWindow* owner, NativeRequest request, NativeCallback callback)
{
    NativeResult rejected;
    if (active)
        rejected.error = {DialogErrorCode::Busy, "The AppKit file dialog is already visible"};
    else if (!owner || !owner.visible || owner.miniaturized)
        rejected.error = {DialogErrorCode::Unavailable, "The file dialog needs a visible application window"};
    else if (owner.attachedSheet)
        rejected.error = {DialogErrorCode::Busy, "The application window already has a sheet"};
    if (rejected.error)
    {
        callback(std::move(rejected));
        return;
    }

    const auto id = request.id;
    const auto types = apple::contentTypes(request.options);
    NSSavePanel* panel;
    if (request.operation == Operation::Open || request.operation == Operation::Folder)
    {
        const bool folder = request.operation == Operation::Folder;
        auto* openPanel = [NSOpenPanel openPanel];
        openPanel.canChooseDirectories = folder;
        openPanel.canChooseFiles = !folder;
        openPanel.allowsMultipleSelection = !folder && request.options.allowMultiple;
        openPanel.treatsFilePackagesAsDirectories = YES;
        openPanel.allowedContentTypes = folder ? @[] : types.types;
        panel = openPanel;
    }
    else
    {
        panel = [NSSavePanel savePanel];
        panel.canCreateDirectories = YES;
        panel.nameFieldStringValue = apple::string(request.suggestedName) ?: @"";
        panel.allowedContentTypes = types.types;
    }
    if (!request.options.title.empty())
        panel.title = apple::string(request.options.title) ?: @"";
    if (NSURL* directory = apple::directoryURL(request.options.initialDirectory))
        panel.directoryURL = directory;

    active = std::make_unique<Presentation>(Presentation{std::move(request), std::move(callback), panel, owner});
    active->validateExtensions = types.needsExtensionCheck;
    active->closeObserver = [[NSNotificationCenter defaultCenter] addObserverForName:NSWindowWillCloseNotification
        object:owner queue:nil usingBlock:^(NSNotification*) {
            if (active && active->request.id == id)
            {
                active->ownerClosed = true;
                [active->panel cancel:nil];
            }
        }];
    [panel beginSheetModalForWindow:owner completionHandler:^(NSModalResponse response) { complete(id, response); }];
}
}

DialogCapabilities nativeCapabilities()
{
    DialogCapabilities capabilities;
    capabilities.backend = "AppKit";
    capabilities.available = capabilities.openFiles = capabilities.multipleFiles = capabilities.pickFolder =
        capabilities.exportFile = capabilities.chooseSaveTarget = capabilities.initialDirectoryHint =
        capabilities.physicalDismiss = true;
    return capabilities;
}

void presentNative(NativeRequest request, NativeCallback callback)
{
    __weak NSWindow* owner = request.view ? request.view->getCocoaWindow() : nil;
    request.view = nullptr;
    if ([NSThread isMainThread])
        present(owner, std::move(request), std::move(callback));
    else
        dispatch_async(dispatch_get_main_queue(), ^{ present(owner, request, callback); });
}

void cancelNative(uint64_t id)
{
    auto close = ^{
        if (active && active->request.id == id)
            [active->panel cancel:nil];
    };
    if ([NSThread isMainThread])
        close();
    else
        dispatch_async(dispatch_get_main_queue(), close);
}

void shutdownNative()
{
    apple::stopCoordinating();
    auto close = ^{ if (active) [active->panel cancel:nil]; };
    if ([NSThread isMainThread])
        close();
    else
        dispatch_async(dispatch_get_main_queue(), close);
}
}
