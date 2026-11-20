#include "platform/desktop/TextInputGLFW.h"
#include "base/ccUTF8.h"
#include "platform/TextInputBackend.h"

#define GLFW_INCLUDE_NONE
#include "glfw3.h"

#include <algorithm>
#include <unordered_map>
#include <utility>

namespace cc
{

#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
std::unique_ptr<TextInputBackend> createWin32TextInputBackend(GLFWwindow* window);
bool isWin32ImeKeyConsumed(GLFWwindow* window);
bool handleWin32TextCharacter(GLFWwindow* window, unsigned int codepoint);
#elif CC_TARGET_PLATFORM == CC_PLATFORM_MAC
std::unique_ptr<TextInputBackend> createMacTextInputBackend(GLFWwindow* window);
bool isMacTextInputResponderActive(GLFWwindow* window);
bool retainsMacTextInputFocus(GLFWwindow* window);
#endif
#ifdef CC_GLFW_X11
std::unique_ptr<TextInputBackend> createX11TextInputBackend(GLFWwindow* window);
bool isX11ImeKeyConsumed(GLFWwindow* window);
void refreshX11TextInputBackends();
#endif
#ifdef CC_GLFW_WAYLAND
std::unique_ptr<TextInputBackend> createWaylandTextInputBackend(GLFWwindow* window);
bool handleWaylandTextCharacter(GLFWwindow* window, unsigned int codepoint);
void pollWaylandTextInput();
#endif

namespace TextInputGLFW
{
namespace
{
struct WindowBinding
{
    TextInputService* service;
    TextInputWindowId id;
    CommitObserver observeCommit = nullptr;
    void* observerUser = nullptr;
#if CC_TARGET_PLATFORM == CC_PLATFORM_MAC
    bool focusLossPending = false;
#endif
};

std::unordered_map<GLFWwindow*, WindowBinding> windows;

class GlfwCharacterBackend final : public TextInputBackend
{
public:
    TextInputCapabilities capabilities() const override { return {}; }
    TextInputError activate(const TextInputActivation& activation) override
    {
        _sink = activation.sink;
        return TextInputError::none;
    }
    void setArea(const std::optional<TextInputArea>&) override {}
    void updateSnapshot(const TextInputSnapshot&) override {}
    TextInputError requestKeyboard(bool) override { return TextInputError::unsupported; }
    TextInputError cancelComposition() override { return TextInputError::unsupported; }
    void deactivate() override
    {
        _sink.closed();
        _sink = {};
    }

private:
    TextInputEventSink _sink;
};

std::optional<TextInputCommandAction> commandForKey(int key, int mods)
{
    using Command = TextInputCommandAction;
    switch (key)
    {
    case GLFW_KEY_BACKSPACE: return Command::backspace;
    case GLFW_KEY_DELETE: return Command::deleteForward;
    case GLFW_KEY_LEFT: return Command::left;
    case GLFW_KEY_RIGHT: return Command::right;
    case GLFW_KEY_UP: return Command::up;
    case GLFW_KEY_DOWN: return Command::down;
    case GLFW_KEY_HOME: return Command::lineStart;
    case GLFW_KEY_END: return Command::lineEnd;
    case GLFW_KEY_ENTER:
    case GLFW_KEY_KP_ENTER: return Command::insertNewline;
    case GLFW_KEY_ESCAPE: return Command::cancel;
    case GLFW_KEY_A:
#if CC_TARGET_PLATFORM == CC_PLATFORM_MAC
        if (mods == GLFW_MOD_SUPER)
#else
        if (mods == GLFW_MOD_CONTROL)
#endif
            return Command::selectAll;
        break;
    default: break;
    }
    return std::nullopt;
}
}  // namespace

TextInputWindowId attachWindow(TextInputService& service,
                               GLFWwindow* window,
                               TextInputService::CoordinateTransform transform)
{
    if (!window)
        return 0;
    auto existing = windows.find(window);
    if (existing != windows.end())
        return existing->second.service == &service ? existing->second.id : 0;

    std::unique_ptr<TextInputBackend> backend;
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
    backend = createWin32TextInputBackend(window);
#elif CC_TARGET_PLATFORM == CC_PLATFORM_MAC
    backend = createMacTextInputBackend(window);
#endif
#ifdef CC_GLFW_X11
    if (glfwGetPlatform() == GLFW_PLATFORM_X11)
        backend = createX11TextInputBackend(window);
#endif
#ifdef CC_GLFW_WAYLAND
    if (glfwGetPlatform() == GLFW_PLATFORM_WAYLAND)
        backend = createWaylandTextInputBackend(window);
#endif
    if (!backend)
        backend = std::make_unique<GlfwCharacterBackend>();
    const auto id = service.registerWindow(std::move(backend), glfwGetWindowAttrib(window, GLFW_FOCUSED) == GLFW_TRUE,
                                           std::move(transform));
    if (id != 0)
        windows.emplace(window, WindowBinding{&service, id});
    return id;
}

void detachWindow(GLFWwindow* window)
{
    const auto entry = windows.find(window);
    if (entry == windows.end())
        return;
    const WindowBinding binding = entry->second;
    windows.erase(entry);
    binding.service->unregisterWindow(binding.id);
}

void detachWindows(TextInputService& service)
{
    for (;;)
    {
        const auto entry = std::find_if(windows.begin(), windows.end(), [&](const auto& binding) {
            return binding.second.service == &service;
        });
        if (entry == windows.end())
            return;
        detachWindow(entry->first);
    }
}

TextInputWindowId getWindow(GLFWwindow* window)
{
    const auto entry = windows.find(window);
    return entry == windows.end() ? 0 : entry->second.id;
}

void handleCharacter(GLFWwindow* window, unsigned int codepoint)
{
    const auto entry = windows.find(window);
    if (entry == windows.end())
        return;
    const auto& binding = entry->second;
    const auto sink = binding.service->sinkForWindow(binding.id);
    if (!sink)
        return;
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
    if (handleWin32TextCharacter(window, codepoint))
        return;
#elif CC_TARGET_PLATFORM == CC_PLATFORM_MAC
    if (isMacTextInputResponderActive(window))
        return;
#elif defined(CC_GLFW_WAYLAND)
    if (handleWaylandTextCharacter(window, codepoint))
        return;
#endif

    const char32_t scalar = static_cast<char32_t>(codepoint);
    std::string utf8;
    if (StringUtils::UTF32ToUTF8({&scalar, 1}, utf8))
        detail::postCommit(window, sink, TextInputCommit{std::move(utf8)});
}

void handleKey(GLFWwindow* window, int key, int mods)
{
    const auto entry = windows.find(window);
    if (entry == windows.end())
        return;
    const auto& binding = entry->second;
    const auto sink = binding.service->sinkForWindow(binding.id);
    if (!sink)
        return;
    if (const auto command = commandForKey(key, mods))
        sink.post(TextInputCommand{*command});
}

bool isKeyConsumed(GLFWwindow* window)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
    return isWin32ImeKeyConsumed(window);
#elif defined(CC_GLFW_X11)
    return isX11ImeKeyConsumed(window);
#else
    return false;
#endif
}

#if CC_TARGET_PLATFORM == CC_PLATFORM_LINUX || CC_TARGET_PLATFORM == CC_PLATFORM_MAC
void pollNativeEvents()
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_MAC
    // AppKit can update its key window after the GLFW focus callback. Recheck on
    // each poll while a system panel owns the key flag and let real transfers close.
    for (;;)
    {
        const auto entry = std::find_if(windows.begin(), windows.end(), [](const auto& binding) {
            return binding.second.focusLossPending && !retainsMacTextInputFocus(binding.first);
        });
        if (entry == windows.end())
            break;
        auto& binding = entry->second;
        binding.focusLossPending = false;
        binding.service->setWindowFocused(binding.id, false);
    }
#endif
#ifdef CC_GLFW_X11
    refreshX11TextInputBackends();
#endif
#ifdef CC_GLFW_WAYLAND
    pollWaylandTextInput();
#endif
}
#endif

void handleFocus(GLFWwindow* window, bool focused)
{
    const auto entry = windows.find(window);
    if (entry == windows.end())
        return;
    auto& binding = entry->second;
#if CC_TARGET_PLATFORM == CC_PLATFORM_MAC
    binding.focusLossPending = !focused;
    if (!focused)
        return;
#endif
    binding.service->setWindowFocused(binding.id, focused);
}

void handleGeometry(GLFWwindow* window)
{
    const auto entry = windows.find(window);
    if (entry != windows.end())
        entry->second.service->geometryChanged(entry->second.id);
}

void setCommitObserver(GLFWwindow* window, CommitObserver observer, void* user)
{
    const auto entry = windows.find(window);
    if (entry != windows.end())
    {
        entry->second.observeCommit = observer;
        entry->second.observerUser = user;
    }
}

void clearCommitObserver(GLFWwindow* window, void* user)
{
    const auto entry = windows.find(window);
    if (entry != windows.end() && entry->second.observerUser == user)
    {
        entry->second.observeCommit = nullptr;
        entry->second.observerUser = nullptr;
    }
}

void detail::postCommit(GLFWwindow* window, const TextInputEventSink& sink, TextInputCommit commit)
{
    if (!sink.post(std::move(commit)))
        return;
    const auto entry = windows.find(window);
    if (entry != windows.end() && entry->second.observeCommit)
        entry->second.observeCommit(entry->second.observerUser, sink.session());
}

}  // namespace TextInputGLFW
}  // namespace cc
