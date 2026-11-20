#pragma once

#include "platform/TextInputService.h"

struct GLFWwindow;

namespace cc::TextInputGLFW
{

CC_DLL TextInputWindowId attachWindow(TextInputService& service,
                                     GLFWwindow* window,
                                     TextInputService::CoordinateTransform transform = {});
CC_DLL void detachWindow(GLFWwindow* window);
CC_DLL void detachWindows(TextInputService& service);
CC_DLL TextInputWindowId getWindow(GLFWwindow* window);

CC_DLL void handleCharacter(GLFWwindow* window, unsigned int codepoint);
CC_DLL void handleKey(GLFWwindow* window, int key, int mods);
CC_DLL bool isKeyConsumed(GLFWwindow* window);
CC_DLL void handleFocus(GLFWwindow* window, bool focused);
CC_DLL void handleGeometry(GLFWwindow* window);
#if CC_TARGET_PLATFORM == CC_PLATFORM_LINUX || CC_TARGET_PLATFORM == CC_PLATFORM_MAC
void pollNativeEvents();
#endif

// The host may record a native input-order boundary without duplicating the commit.
using CommitObserver = void (*)(void* user, TextInputSessionId session);
CC_DLL void setCommitObserver(GLFWwindow* window, CommitObserver observer, void* user);
CC_DLL void clearCommitObserver(GLFWwindow* window, void* user);

namespace detail
{
void postCommit(GLFWwindow* window, const TextInputEventSink& sink, TextInputCommit commit);
}

}  // namespace cc::TextInputGLFW
