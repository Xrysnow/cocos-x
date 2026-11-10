/****************************************************************************
 MIT License

 Portions copyright (c) 2017 Serge Zaitsev

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

#include "platform/CCPlatformConfig.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 && defined(CC_ENABLE_MSEDGE_WEBVIEW2) && CC_ENABLE_MSEDGE_WEBVIEW2

#include "UIWebViewImpl-win32.h"
#include "UIWebView.h"
#include "base/CCDirector.h"
#include "base/CCRefPtr.h"
#include "base/ccUtils.h"
#include "platform/CCFileUtils.h"
#include "platform/CCGLView.h"
#include "ui/UIHelper.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <Shlwapi.h>
#include <wrl.h>
#include <cstdlib>
#include <memory>
#include <string>
#include <utility>
#include "WebView2.h"
#include "ntcvt/ntcvt.hpp"

#pragma comment(lib, "user32.lib")
#pragma comment(lib, "Shlwapi.lib")
#pragma comment(lib, "ole32.lib")
#pragma comment(lib, "oleaut32.lib")

USING_NS_CC;
using Microsoft::WRL::Callback;
using Microsoft::WRL::ComPtr;

namespace
{
// WebView2 does not support nested message loops inside its callbacks. A
// synchronous create/clone in such a callback must fail rather than hang.
thread_local unsigned webViewCallbackDepth = 0;
struct WebViewCallbackScope
{
    WebViewCallbackScope() { ++webViewCallbackDepth; }
    ~WebViewCallbackScope() { --webViewCallbackDepth; }
};

std::wstring toWide(std::string_view text)
{
    if (text.empty())
        return {};
    const int length = MultiByteToWideChar(CP_UTF8, 0, text.data(), static_cast<int>(text.size()), nullptr, 0);
    std::wstring result(length, L'\0');
    if (length)
        MultiByteToWideChar(CP_UTF8, 0, text.data(), static_cast<int>(text.size()), result.data(), length);
    return result;
}

std::string takeUtf8(LPWSTR text)
{
    std::string result;
    if (text)
        result = ntcvt::from_chars(text, CP_UTF8);
    CoTaskMemFree(text);
    return result;
}

std::string sourceURL(ICoreWebView2* view)
{
    LPWSTR uri = nullptr;
    if (view)
        view->get_Source(&uri);
    return takeUtf8(uri);
}

std::string htmlFromUri(std::string_view text)
{
    return text.substr(0, 15) == "data:text/html," ? utils::urlDecode(text.substr(15)) : std::string{};
}

std::string getDataURI(std::string_view data, std::string_view mimeType)
{
    return std::string{"data:"}.append(mimeType).append(";base64,").append(utils::urlEncode(utils::base64Encode(data)));
}

double getDeviceScaleFactor()
{
    HDC screen = GetDC(nullptr);
    const double scale = static_cast<double>(GetDeviceCaps(screen, LOGPIXELSX)) / 96.0;
    ReleaseDC(nullptr, screen);
    return scale;
}
}  // namespace

class Win32WebControl
{
    enum class Phase { Uncreated, Creating, Ready, Closing, Closed, Failed };
    struct Apartment
    {
        const bool initialized = SUCCEEDED(CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED));
        ~Apartment()
        {
            if (initialized)
                CoUninitialize();
        }
    };
    struct Token
    {
        EventRegistrationToken value{};
        bool installed = false;
    };
    struct State
    {
        Phase phase = Phase::Uncreated;
        const DWORD thread = GetCurrentThreadId();
        // Async completion handlers and event callback objects also hold this
        // lease, keeping COM initialized after an owner closes in a callback.
        const std::shared_ptr<Apartment> apartment = std::make_shared<Apartment>();
        HWND window = nullptr;
        ComPtr<ICoreWebView2> webview;
        ComPtr<ICoreWebView2Controller> controller;
        Token message, permission, starting, completed, newWindow;
        std::string jsScheme;
        bool scalesPageToFit = false;
        std::function<bool(std::string_view)> shouldStart;
        std::function<void(std::string_view)> didFinish, didFail, onJS;

        bool ready() const { return phase == Phase::Ready && thread == GetCurrentThreadId(); }
        void close()
        {
            if (phase == Phase::Closing || phase == Phase::Closed)
                return;
            phase = Phase::Closing;
            // Invalidate notification owners before COM calls can reenter us.
            shouldStart = nullptr;
            didFinish = didFail = onJS = nullptr;
            auto view = std::move(webview);
            auto control = std::move(controller);
            if (view)
            {
                if (message.installed) view->remove_WebMessageReceived(message.value);
                if (permission.installed) view->remove_PermissionRequested(permission.value);
                if (starting.installed) view->remove_NavigationStarting(starting.value);
                if (completed.installed) view->remove_NavigationCompleted(completed.value);
                if (newWindow.installed) view->remove_NewWindowRequested(newWindow.value);
            }
            message = permission = starting = completed = newWindow = {};
            if (control)
                control->Close();
            const auto hwnd = std::exchange(window, nullptr);
            if (hwnd && IsWindow(hwnd))
            {
                SetWindowLongPtr(hwnd, GWLP_USERDATA, 0);
                DestroyWindow(hwnd);
            }
            phase = Phase::Closed;
        }
    };

public:
    Win32WebControl() = default;
    ~Win32WebControl() { removeWebView(); }

    bool createWebView(const std::function<bool(std::string_view)>& shouldStart,
                       const std::function<void(std::string_view)>& didFinish,
                       const std::function<void(std::string_view)>& didFail,
                       const std::function<void(std::string_view)>& onJS)
    {
        const auto state = _state;
        if (!state->apartment->initialized || webViewCallbackDepth || state->phase != Phase::Uncreated)
            return false;
        state->phase = Phase::Creating;
        state->shouldStart = shouldStart;
        state->didFinish = didFinish;
        state->didFail = didFail;
        state->onJS = onJS;
        const auto hostView = Director::getInstance()->getOpenGLView();
        const auto parent = hostView ? hostView->getWin32Window() : nullptr;
        if (!parent || !IsWindow(parent))
        {
            state->close();
            return false;
        }
        SetWindowLongPtr(parent, GWL_STYLE, GetWindowLongPtr(parent, GWL_STYLE) | WS_CLIPCHILDREN);
        const auto instance = GetModuleHandle(nullptr);
        WNDCLASSEXW windowClass{};
        windowClass.cbSize = sizeof(windowClass);
        windowClass.hInstance = instance;
        windowClass.lpszClassName = L"cocos-webview";
        windowClass.lpfnWndProc = windowProcedure;
        if (!RegisterClassExW(&windowClass) && GetLastError() != ERROR_CLASS_ALREADY_EXISTS)
        {
            state->close();
            return false;
        }
        state->window = CreateWindowExW(0, windowClass.lpszClassName, L"", WS_VISIBLE | WS_CHILD,
                                        0, 0, 0, 0, parent, nullptr, instance, state.get());
        if (!state->window)
        {
            state->close();
            return false;
        }
        char executable[MAX_PATH]{};
        const auto executableLength = GetModuleFileNameA(nullptr, executable, MAX_PATH);
        const char* appData = std::getenv("APPDATA");
        if (!appData || !executableLength || executableLength >= MAX_PATH)
        {
            state->close();
            return false;
        }
        const auto userData = ntcvt::from_chars(appData, CP_ACP) + L"/" +
                              ntcvt::from_chars(PathFindFileNameA(executable), CP_ACP);
        const HRESULT result = CreateCoreWebView2EnvironmentWithOptions(nullptr, userData.c_str(), nullptr,
            Callback<ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandler>(
                [state](HRESULT result, ICoreWebView2Environment* environment) -> HRESULT {
                    if (state->phase != Phase::Creating)
                        return S_OK;
                    if (FAILED(result) || !environment)
                    {
                        state->phase = Phase::Failed;
                        return S_OK;
                    }
                    const HRESULT controllerResult = environment->CreateCoreWebView2Controller(state->window,
                        Callback<ICoreWebView2CreateCoreWebView2ControllerCompletedHandler>(
                            [state](HRESULT result, ICoreWebView2Controller* controller) -> HRESULT {
                                if (state->phase != Phase::Creating)
                                {
                                    if (controller) controller->Close();
                                    return S_OK;
                                }
                                if (FAILED(result) || !controller)
                                {
                                    state->phase = Phase::Failed;
                                    return S_OK;
                                }
                                const ComPtr<ICoreWebView2Controller> control = controller;
                                state->controller = control;
                                ComPtr<ICoreWebView2> view;
                                const HRESULT viewResult = control->get_CoreWebView2(view.GetAddressOf());
                                if (state->phase != Phase::Creating)
                                {
                                    control->Close();
                                    return S_OK;
                                }
                                if (FAILED(viewResult) || !view)
                                {
                                    state->phase = Phase::Failed;
                                    return S_OK;
                                }
                                state->webview = view;
                                if (!installEvents(state))
                                {
                                    if (state->phase == Phase::Creating)
                                        state->phase = Phase::Failed;
                                    return S_OK;
                                }
                                if (state->phase != Phase::Creating)
                                    return S_OK;
                                state->phase = Phase::Ready;
                                RECT bounds{};
                                GetClientRect(state->window, &bounds);
                                control->put_Bounds(bounds);
                                if (state->ready())
                                    view->AddScriptToExecuteOnDocumentCreated(
                                        L"window.external={invoke:s=>window.chrome.webview.postMessage(s)}", nullptr);
                                return S_OK;
                            }).Get());
                    if (FAILED(controllerResult) && state->phase == Phase::Creating)
                        state->phase = Phase::Failed;
                    return S_OK;
                }).Get());
        if (FAILED(result) && state->phase == Phase::Creating)
            state->phase = Phase::Failed;

        // Preserve synchronous factory failure semantics without an unbounded
        // GetMessage wait. Completion handlers own only state, never this.
        const auto deadline = GetTickCount64() + 30000;
        while (state->phase == Phase::Creating && GetTickCount64() < deadline)
        {
            MsgWaitForMultipleObjectsEx(0, nullptr, 50, QS_ALLINPUT, MWMO_INPUTAVAILABLE);
            MSG message{};
            while (state->phase == Phase::Creating && GetTickCount64() < deadline &&
                   PeekMessage(&message, nullptr, 0, 0, PM_REMOVE))
            {
                if (message.message == WM_QUIT)
                {
                    PostQuitMessage(static_cast<int>(message.wParam));
                    state->phase = Phase::Failed;
                    break;
                }
                TranslateMessage(&message);
                DispatchMessage(&message);
            }
        }
        if (!state->ready())
        {
            state->close();
            CCLOG("Cannot initialize WebView2 (creation failed, closed, or timed out)");
            return false;
        }
        return true;
    }

    void removeWebView() { _state->close(); }
    bool isInitialized() const { return _state->ready(); }
    void setWebViewRect(int left, int top, int width, int height)
    {
        const auto state = _state;
        if (!state->ready()) return;
        const auto controller = state->controller;
        SetWindowPos(state->window, nullptr, left, top, width, height, SWP_NOZORDER);
        if (!state->ready()) return;
        RECT bounds{};
        GetClientRect(state->window, &bounds);
        controller->put_Bounds(bounds);
        if (state->ready()) controller->put_ZoomFactor(state->scalesPageToFit ? getDeviceScaleFactor() : 1.0);
    }
    void setJavascriptInterfaceScheme(std::string_view scheme) { _state->jsScheme = scheme; }
    void loadHTMLString(std::string_view html, std::string_view)
    {
        const auto state = _state;
        const auto view = state->webview;
        if (state->ready()) view->NavigateToString(toWide(html).c_str());
    }
    void loadURL(std::string_view url, bool cleanCachedData)
    {
        const auto state = _state;
        if (!state->ready()) return;
        const auto view = state->webview;
        if (cleanCachedData) view->CallDevToolsProtocolMethod(L"Network.clearBrowserCache", L"{}", nullptr);
        if (state->ready()) view->Navigate(toWide(url).c_str());
    }
    void loadFile(std::string_view file)
    {
        auto path = FileUtils::getInstance()->fullPathForFilename(file);
        if (path.find("file:///") != 0)
            path = (path.empty() || path.front() != '/' ? "file:///" : "file://") + path;
        loadURL(path, false);
    }
    void stopLoading()
    {
        const auto state = _state;
        const auto view = state->webview;
        if (state->ready()) view->Stop();
    }
    void reload()
    {
        const auto state = _state;
        const auto view = state->webview;
        if (state->ready()) view->Reload();
    }
    bool canGoBack() const
    {
        BOOL result = FALSE;
        const auto state = _state;
        const auto view = state->webview;
        return state->ready() && SUCCEEDED(view->get_CanGoBack(&result)) && result;
    }
    bool canGoForward() const
    {
        BOOL result = FALSE;
        const auto state = _state;
        const auto view = state->webview;
        return state->ready() && SUCCEEDED(view->get_CanGoForward(&result)) && result;
    }
    void goBack()
    {
        const auto state = _state;
        const auto view = state->webview;
        if (state->ready()) view->GoBack();
    }
    void goForward()
    {
        const auto state = _state;
        const auto view = state->webview;
        if (state->ready()) view->GoForward();
    }
    void evaluateJS(std::string_view js)
    {
        const auto state = _state;
        const auto view = state->webview;
        if (state->ready()) view->ExecuteScript(toWide(js).c_str(), nullptr);
    }
    void setScalesPageToFit(bool scalesPageToFit)
    {
        const auto state = _state;
        const auto controller = state->controller;
        state->scalesPageToFit = scalesPageToFit;
        if (state->ready()) controller->put_ZoomFactor(scalesPageToFit ? getDeviceScaleFactor() : 1.0);
    }
    void setWebViewVisible(bool visible)
    {
        const auto state = _state;
        if (!state->ready()) return;
        ShowWindow(state->window, visible ? SW_SHOW : SW_HIDE);
        if (!visible && state->ready())
            SetWindowPos(state->window, nullptr, 0, 0, 0, 0, SWP_NOZORDER | SWP_NOMOVE | SWP_NOACTIVATE);
    }
    void setBounces(bool) {}
    void setOpacityWebView(float) {}
    float getOpacityWebView() const { return 1.0f; }
    void setBackgroundTransparent()
    {
        const auto state = _state;
        const auto baseController = state->controller;
        if (!state->ready()) return;
        ComPtr<ICoreWebView2Controller2> controller;
        if (SUCCEEDED(baseController.As(&controller)))
        {
            COREWEBVIEW2_COLOR color{};
            if (SUCCEEDED(controller->get_DefaultBackgroundColor(&color)))
            {
                color.A = 0;
                controller->put_DefaultBackgroundColor(color);
            }
        }
    }

private:
    static LRESULT CALLBACK windowProcedure(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
    {
        auto state = reinterpret_cast<State*>(GetWindowLongPtr(window, GWLP_USERDATA));
        if (message == WM_NCCREATE)
        {
            state = static_cast<State*>(reinterpret_cast<CREATESTRUCT*>(lparam)->lpCreateParams);
            SetWindowLongPtr(window, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(state));
        }
        if (state && message == WM_SIZE && state->controller)
        {
            const auto controller = state->controller;
            RECT bounds{};
            GetClientRect(window, &bounds);
            controller->put_Bounds(bounds);
        }
        if (state && message == WM_NCDESTROY)
        {
            SetWindowLongPtr(window, GWLP_USERDATA, 0);
            state->window = nullptr;
            state->close();
        }
        return DefWindowProc(window, message, wparam, lparam);
    }

    static bool installEvents(const std::shared_ptr<State>& state)
    {
        const std::weak_ptr<State> weak = state;
        const auto apartment = state->apartment;
        const auto view = state->webview;
        const auto install = [&](Token& slot, auto add, auto remove, const auto& handler) {
            if (state->phase != Phase::Creating)
                return false;
            EventRegistrationToken token{};
            if (FAILED((view.Get()->*add)(handler.Get(), &token)))
                return false;
            if (state->phase != Phase::Creating)
            {
                // A window/owner close during registration cannot publish a
                // token into a closed state or leave this new handler installed.
                (view.Get()->*remove)(token);
                return false;
            }
            slot.value = token;
            slot.installed = true;
            return true;
        };
        if (!install(state->message, &ICoreWebView2::add_WebMessageReceived,
                     &ICoreWebView2::remove_WebMessageReceived,
            Callback<ICoreWebView2WebMessageReceivedEventHandler>(
                [weak, apartment](ICoreWebView2* sender, ICoreWebView2WebMessageReceivedEventArgs* args) -> HRESULT {
                    const auto state = weak.lock();
                    if (!state || !state->ready()) return S_OK;
                    WebViewCallbackScope scope;
                    LPWSTR text = nullptr;
                    if (SUCCEEDED(args->TryGetWebMessageAsString(&text)) && text)
                        sender->PostWebMessageAsString(text);
                    CoTaskMemFree(text);
                    return S_OK;
                }))) return false;
        if (!install(state->permission, &ICoreWebView2::add_PermissionRequested,
                     &ICoreWebView2::remove_PermissionRequested,
            Callback<ICoreWebView2PermissionRequestedEventHandler>(
                [weak, apartment](ICoreWebView2*, ICoreWebView2PermissionRequestedEventArgs* args) -> HRESULT {
                    const auto state = weak.lock();
                    if (!state || !state->ready()) return S_OK;
                    WebViewCallbackScope scope;
                    COREWEBVIEW2_PERMISSION_KIND kind{};
                    if (SUCCEEDED(args->get_PermissionKind(&kind)) && kind == COREWEBVIEW2_PERMISSION_KIND_CLIPBOARD_READ)
                        args->put_State(COREWEBVIEW2_PERMISSION_STATE_ALLOW);
                    return S_OK;
                }))) return false;
        if (!install(state->starting, &ICoreWebView2::add_NavigationStarting,
                     &ICoreWebView2::remove_NavigationStarting,
            Callback<ICoreWebView2NavigationStartingEventHandler>(
                [weak, apartment](ICoreWebView2*, ICoreWebView2NavigationStartingEventArgs* args) -> HRESULT {
                    const auto state = weak.lock();
                    if (!state || !state->ready())
                    {
                        args->put_Cancel(TRUE);
                        return S_OK;
                    }
                    WebViewCallbackScope scope;
                    LPWSTR uri = nullptr;
                    if (FAILED(args->get_Uri(&uri)) || !uri)
                    {
                        CoTaskMemFree(uri);
                        args->put_Cancel(TRUE);
                        return S_OK;
                    }
                    const auto url = takeUtf8(uri);
                    const auto js = state->onJS;
                    const auto shouldStart = state->shouldStart;
                    const auto scheme = url.substr(0, url.find(':'));
                    bool allow = true;
                    if (scheme == state->jsScheme)
                    {
                        if (js) js(url);
                    }
                    else if (shouldStart)
                    {
                        allow = shouldStart(url);
                    }
                    if (!allow || !state->ready()) args->put_Cancel(TRUE);
                    return S_OK;
                }))) return false;
        if (!install(state->completed, &ICoreWebView2::add_NavigationCompleted,
                     &ICoreWebView2::remove_NavigationCompleted,
            Callback<ICoreWebView2NavigationCompletedEventHandler>(
                [weak, apartment](ICoreWebView2* sender, ICoreWebView2NavigationCompletedEventArgs* args) -> HRESULT {
                    const auto state = weak.lock();
                    if (!state || !state->ready()) return S_OK;
                    WebViewCallbackScope scope;
                    BOOL success = FALSE;
                    const auto callback = SUCCEEDED(args->get_IsSuccess(&success)) && success ? state->didFinish : state->didFail;
                    const auto url = sourceURL(sender);
                    if (callback) callback(url);
                    return S_OK;
                }))) return false;
        if (!install(state->newWindow, &ICoreWebView2::add_NewWindowRequested,
                     &ICoreWebView2::remove_NewWindowRequested,
            Callback<ICoreWebView2NewWindowRequestedEventHandler>(
                [weak, apartment](ICoreWebView2*, ICoreWebView2NewWindowRequestedEventArgs* args) -> HRESULT {
                    // Keep the existing no-popup policy. A separate browser
                    // owner is deliberately not created during this event.
                    const auto state = weak.lock();
                    if (state) args->put_Handled(TRUE);
                    return S_OK;
                }))) return false;
        return state->phase == Phase::Creating;
    }

    std::shared_ptr<State> _state = std::make_shared<State>();
};

NS_CC_BEGIN
namespace ui
{
WebViewImpl::WebViewImpl(WebView* webView) : _systemWebControl(new Win32WebControl()), _webView(webView)
{
    _systemWebControl->createWebView(
        [webView](std::string_view url) -> bool {
            const RefPtr<WebView> sender(webView);
            const auto callback = sender->getOnShouldStartLoading();
            return callback ? callback(sender.get(), url) : true;
        },
        [webView](std::string_view url) {
            const RefPtr<WebView> sender(webView);
            const auto callback = sender->getOnDidFinishLoading();
            if (callback) callback(sender.get(), url);
        },
        [webView](std::string_view url) {
            const RefPtr<WebView> sender(webView);
            const auto callback = sender->getOnDidFailLoading();
            if (callback) callback(sender.get(), url);
        },
        [webView](std::string_view url) {
            const RefPtr<WebView> sender(webView);
            const auto callback = sender->getOnJSCallback();
            if (callback) callback(sender.get(), url);
        });
}

WebViewImpl::~WebViewImpl() { delete _systemWebControl; }
bool WebViewImpl::isInitialized() const { return _systemWebControl && _systemWebControl->isInitialized(); }

void WebViewImpl::loadData(const Data& data, std::string_view MIMEType, std::string_view, std::string_view)
{
    if (isInitialized())
        _systemWebControl->loadURL(getDataURI(std::string_view(reinterpret_cast<const char*>(data.getBytes()), data.getSize()), MIMEType), false);
}
void WebViewImpl::loadHTMLString(std::string_view text, std::string_view baseURL)
{
    if (!isInitialized()) return;
    const auto html = htmlFromUri(text);
    _systemWebControl->loadHTMLString(text.empty() ? std::string_view("<html></html>") :
                                    html.empty() ? text : std::string_view(html), baseURL);
}
void WebViewImpl::loadURL(std::string_view url, bool cleanCachedData) { _systemWebControl->loadURL(url, cleanCachedData); }
void WebViewImpl::loadFile(std::string_view file) { _systemWebControl->loadFile(file); }
void WebViewImpl::stopLoading() { _systemWebControl->stopLoading(); }
void WebViewImpl::reload() { _systemWebControl->reload(); }
bool WebViewImpl::canGoBack() { return _systemWebControl->canGoBack(); }
bool WebViewImpl::canGoForward() { return _systemWebControl->canGoForward(); }
void WebViewImpl::goBack() { _systemWebControl->goBack(); }
void WebViewImpl::goForward() { _systemWebControl->goForward(); }
void WebViewImpl::setJavascriptInterfaceScheme(std::string_view scheme) { _systemWebControl->setJavascriptInterfaceScheme(scheme); }
void WebViewImpl::evaluateJS(std::string_view js) { _systemWebControl->evaluateJS(js); }
void WebViewImpl::setScalesPageToFit(bool scalesPageToFit) { _systemWebControl->setScalesPageToFit(scalesPageToFit); }
void WebViewImpl::draw(Renderer*, Mat4 const&, uint32_t flags)
{
    if (isInitialized() && (flags & Node::FLAGS_TRANSFORM_DIRTY))
    {
        const auto rect = Helper::convertBoundingBoxToScreen(_webView);
        _systemWebControl->setWebViewRect(static_cast<int>(rect.origin.x), static_cast<int>(rect.origin.y),
                                        static_cast<int>(rect.size.width), static_cast<int>(rect.size.height));
    }
}
void WebViewImpl::setVisible(bool visible) { _systemWebControl->setWebViewVisible(visible); }
void WebViewImpl::setBounces(bool bounces) { _systemWebControl->setBounces(bounces); }
void WebViewImpl::setOpacityWebView(float opacity) { _systemWebControl->setOpacityWebView(opacity); }
float WebViewImpl::getOpacityWebView() const { return _systemWebControl->getOpacityWebView(); }
void WebViewImpl::setBackgroundTransparent() { _systemWebControl->setBackgroundTransparent(); }
}  // namespace ui
NS_CC_END

#endif  // Win32 WebView2
