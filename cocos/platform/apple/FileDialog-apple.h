#pragma once

#import <Foundation/Foundation.h>
#import <UniformTypeIdentifiers/UniformTypeIdentifiers.h>

#include "platform/FileDialogInternal.h"

namespace cc::dialog::apple
{
void stopCoordinating();
NSString* string(const std::string& value);
std::string string(NSString* value);
NSURL* directoryURL(const std::optional<DocumentHandle>& directory);
DocumentHandle document(NSURL* url, DocumentKind kind);
DocumentHandle saveLocation(NSURL* url, FileDialogError& error);

struct ContentTypes
{
    NSArray<UTType*>* types;
    bool needsExtensionCheck = false;
};

ContentTypes contentTypes(const OpenFileOptions& options);
NativeResult selection(NSArray<NSURL*>* urls, const NativeRequest& request, bool validateExtensions);
}
