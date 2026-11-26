#include "platform/DisplayInternal.h"
#include "platform/desktop/GLViewImpl-desktop.h"
#include <algorithm>
#include <memory>
#include <cmath>
#ifdef CC_GLFW_X11
#define GLFW_EXPOSE_NATIVE_X11
#include <X11/Xatom.h>
#include <X11/Xresource.h>
#endif
#ifdef CC_GLFW_WAYLAND
#define GLFW_EXPOSE_NATIVE_WAYLAND
#endif
#include "glfw3native.h"

namespace cc::display {
namespace {
Key monitorKey(GLFWmonitor* monitor)
{
#ifdef CC_GLFW_X11
    if (glfwGetPlatform() == GLFW_PLATFORM_X11) return glfwGetX11Monitor(monitor);
#endif
#ifdef CC_GLFW_WAYLAND
    if (glfwGetPlatform() == GLFW_PLATFORM_WAYLAND) return reinterpret_cast<Key>(glfwGetWaylandMonitor(monitor));
#endif
    return 0;
}

GLFWmonitor* findMonitor(Key key)
{
    int count = 0;
    auto list = glfwGetMonitors(&count);
    for (int i = 0; key && i < count; ++i)
        if (monitorKey(list[i]) == key) return list[i];
    return nullptr;
}

#ifdef CC_GLFW_X11
template<class T, auto Free>
using Owned = std::unique_ptr<T, decltype(Free)>;
struct Layout {
    ::Display* connection;
    Window root;
    Owned<XRRScreenResources, XRRFreeScreenResources> resources;
    explicit Layout(::Display* d, Window window)
        : connection(d), root(window), resources(XRRGetScreenResourcesCurrent(d, window), XRRFreeScreenResources) {}
    Owned<XRROutputInfo, XRRFreeOutputInfo> output(RROutput id) const
    {
        return {XRRGetOutputInfo(connection, resources.get(), id), XRRFreeOutputInfo};
    }
    Owned<XRRCrtcInfo, XRRFreeCrtcInfo> crtc(RRCrtc id) const
    {
        return {XRRGetCrtcInfo(connection, resources.get(), id), XRRFreeCrtcInfo};
    }
};

bool hasRandR(::Display* connection, int minorVersion)
{
    int eventBase, errorBase, major, minor;
    return connection && XRRQueryExtension(connection, &eventBase, &errorBase) &&
           XRRQueryVersion(connection, &major, &minor) &&
           (major > 1 || (major == 1 && minor >= minorVersion));
}

std::vector<unsigned long> cardinals(::Display* d, Window root, const char* name)
{
    Atom atom = XInternAtom(d, name, True), type;
    int format;
    unsigned long n, remaining;
    unsigned char* data = nullptr;
    std::vector<unsigned long> values;
    if (atom && XGetWindowProperty(d, root, atom, 0, 4096, False, XA_CARDINAL, &type, &format, &n,
                                   &remaining, &data) == Success && type == XA_CARDINAL && format == 32 && !remaining && data) {
        auto* first = reinterpret_cast<unsigned long*>(data);
        values.assign(first, first + n);
    }
    if (data) XFree(data);
    return values;
}

void readWorkArea(DisplayInfo& info, const Layout& layout)
{
    auto current = cardinals(layout.connection, layout.root, "_NET_CURRENT_DESKTOP");
    auto areas = cardinals(layout.connection, layout.root, "_NET_WORKAREA");
    if (current.size() != 1 || current[0] >= areas.size()/4) return;
    const auto* a = areas.data() + 4 * current[0];
    const auto r = *info.geometry;
    int64_t x = std::max<int64_t>(r.x, int32_t(a[0])), y = std::max<int64_t>(r.y, int32_t(a[1]));
    int64_t right = std::min<int64_t>(int64_t(r.x)+r.width, int64_t(int32_t(a[0])) + int64_t(a[2]));
    int64_t bottom = std::min<int64_t>(int64_t(r.y)+r.height, int64_t(int32_t(a[1])) + int64_t(a[3]));
    if (right >= x && bottom >= y) info.availableGeometry = DisplayRect{int(x),int(y),int(right-x),int(bottom-y)};
}

Key windowOutput(GLFWwindow* window)
{
    auto d = glfwGetX11Display();
    if (!hasRandR(d, 3)) return 0;
    Window w = glfwGetX11Window(window), child;
    XWindowAttributes attr{};
    int x, y;
    if (!XGetWindowAttributes(d, w, &attr) || attr.map_state != IsViewable ||
        !XTranslateCoordinates(d, w, attr.root, 0, 0, &x, &y, &child)) return 0;
    Layout layout(d, attr.root);
    if (!layout.resources) return 0;
    Key selected = 0;
    int64_t best = 0;
    for (int i = 0; i < layout.resources->noutput; ++i) {
        auto id = layout.resources->outputs[i];
        auto out = layout.output(id);
        if (!out) return 0;
        if (!out->crtc || out->connection != RR_Connected) continue;
        auto crtc = layout.crtc(out->crtc);
        if (!crtc) return 0;
        const int64_t width = std::min<int64_t>(int64_t(x)+attr.width, int64_t(crtc->x)+crtc->width) - std::max(x, crtc->x);
        const int64_t height = std::min<int64_t>(int64_t(y)+attr.height, int64_t(crtc->y)+crtc->height) - std::max(y, crtc->y);
        if (width <= 0 || height <= 0) continue;
        auto area = width * height;
        if (area > best) { best = area; selected = id; }
        else if (area == best) selected = 0;
    }
    return selected;
}
#endif
}

std::optional<Keys> enumerate()
{
    if (!glfwGetPlatform()) return {};
    int count = 0;
    auto list = glfwGetMonitors(&count);
    Keys keys;
    for (int i = 0; i < count; ++i) {
        auto key = monitorKey(list[i]);
        if (!key) return {};
        keys.push_back(key);
    }
    return keys;
}
Key primary()
{
#ifdef CC_GLFW_X11
    if (glfwGetPlatform() == GLFW_PLATFORM_X11) {
        auto d = glfwGetX11Display();
        if (hasRandR(d, 3)) return XRRGetOutputPrimary(d, DefaultRootWindow(d));
    }
#endif
    return 0;
}
std::optional<DisplayInfo> read(Key key)
{
    auto* monitor = findMonitor(key);
    if (!monitor) return {};
    DisplayInfo info;
    if (auto name = glfwGetMonitorName(monitor)) info.name = name;
    if (auto mode = glfwGetVideoMode(monitor); mode && mode->refreshRate > 0) info.refreshRateHz = mode->refreshRate;
#ifdef CC_GLFW_X11
    if (glfwGetPlatform() == GLFW_PLATFORM_X11) {
        auto d = glfwGetX11Display();
        Layout layout(d, DefaultRootWindow(d));
        if (!layout.resources) return {};
        auto out = layout.output(key);
        if (!out || !out->crtc || out->connection != RR_Connected) return {};
        auto c = layout.crtc(out->crtc);
        if (!c) return {};
        info.coordinateSpace = DisplayCoordinateSpace::Desktop;
        info.geometry = DisplayRect{c->x, c->y, int(c->width), int(c->height)};
        if (auto keys = enumerate(); keys && keys->size() == 1) readWorkArea(info, layout);
        const bool rotated = c->rotation & (RR_Rotate_90 | RR_Rotate_270);
        if (out->mm_width && out->mm_height && out->mm_width <= INT32_MAX && out->mm_height <= INT32_MAX) {
            DisplaySize mm{int(out->mm_width), int(out->mm_height)};
            if (rotated) std::swap(mm.width, mm.height);
            info.physicalSizeMm = mm;
        }
        for (int i = 0; i < layout.resources->nmode; ++i) {
            const auto& mode = layout.resources->modes[i];
            if (mode.id != c->mode) continue;
            DisplaySize size{int(mode.width), int(mode.height)};
            if (rotated) std::swap(size.width, size.height);
            info.pixelSize = size;
            if (mode.hTotal && mode.vTotal && mode.dotClock) {
                double hz = double(mode.dotClock) / mode.hTotal / mode.vTotal;
                if (mode.modeFlags & RR_Interlace) hz *= 2;
                if (mode.modeFlags & RR_DoubleScan) hz /= 2;
                info.refreshRateHz = hz;
            }
            break;
        }
        info.devicePixelRatio = 1.;
        if (const char* resources = XResourceManagerString(d)) {
            auto db = XrmGetStringDatabase(resources);
            XrmValue value{};
            char* type = nullptr;
            if (db && XrmGetResource(db, "Xft.dpi", "Xft.Dpi", &type, &value) && value.addr) {
                char* end = nullptr;
                double dpi = std::strtod(value.addr, &end);
                if (end != value.addr && !*end && std::isfinite(dpi) && dpi > 0) info.logicalDpi = DisplayAxisValues{dpi,dpi};
            }
            if (db) XrmDestroyDatabase(db);
        }
    }
#endif
    return info;
}
}

namespace cc {
std::optional<DisplayInfo> GLViewImpl::getCurrentDisplayInfo() const
{
#ifdef CC_GLFW_X11
    if (_mainWindow && glfwGetPlatform() == GLFW_PLATFORM_X11)
        return display::snapshot(display::windowOutput(_mainWindow));
#endif
    return {};
}
GLFWmonitor* GLViewImpl::resolveDisplayMonitor(DisplayId id)
{
    return display::findMonitor(display::keyForId(id));
}
}
